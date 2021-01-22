// RTSSSharedMemoryInterface.cpp: implementation of the CRTSSSharedMemoryInterface class.
//
// created by Unwinder
//////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "RTSSSharedMemoryInterface.h"

#include <RTSSSharedMemory.h>
#include <float.h>
//////////////////////////////////////////////////////////////////////
CRTSSSharedMemoryInterface::CRTSSSharedMemoryInterface()
{
}
//////////////////////////////////////////////////////////////////////
CRTSSSharedMemoryInterface::~CRTSSSharedMemoryInterface()
{
}
//////////////////////////////////////////////////////////////////////
BOOL CRTSSSharedMemoryInterface::UpdateOSD(LPCSTR lpOSDOwner, LPCSTR lpText)
{
	BOOL bResult	= FALSE;

	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"RTSSSharedMemoryV2");

	if (hMapFile)
	{
		LPVOID pMapAddr				= MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		LPRTSS_SHARED_MEMORY pMem	= (LPRTSS_SHARED_MEMORY)pMapAddr;

		if (pMem)
		{
			if ((pMem->dwSignature == 'RTSS') && 
				(pMem->dwVersion >= 0x00020000))
			{
				for (DWORD dwPass=0; dwPass<2; dwPass++)
					//1st pass : find previously captured OSD slot
					//2nd pass : otherwise find the first unused OSD slot and capture it
				{
					for (DWORD dwEntry=1; dwEntry<pMem->dwOSDArrSize; dwEntry++)
						//allow primary OSD clients (i.e. EVGA Precision / MSI Afterburner) to use the first slot exclusively, so third party
						//applications start scanning the slots from the second one
					{
						RTSS_SHARED_MEMORY::LPRTSS_SHARED_MEMORY_OSD_ENTRY pEntry = (RTSS_SHARED_MEMORY::LPRTSS_SHARED_MEMORY_OSD_ENTRY)((LPBYTE)pMem + pMem->dwOSDArrOffset + dwEntry * pMem->dwOSDEntrySize);

						if (dwPass)
						{
							if (!strlen(pEntry->szOSDOwner))
								strcpy_s(pEntry->szOSDOwner, sizeof(pEntry->szOSDOwner), lpOSDOwner);
						}

						if (!strcmp(pEntry->szOSDOwner, lpOSDOwner))
						{
							if (pMem->dwVersion >= 0x00020007)
								//use extended text slot for v2.7 and higher shared memory, it allows displaying 4096 symbols
								//instead of 256 for regular text slot
							{
								if (pMem->dwVersion >= 0x0002000e)	
									//OSD locking is supported on v2.14 and higher shared memory
								{
									DWORD dwBusy = _interlockedbittestandset(&pMem->dwBusy, 0);
										//bit 0 of this variable will be set if OSD is locked by renderer and cannot be refreshed
										//at the moment

									if (!dwBusy)
									{
										strncpy_s(pEntry->szOSDEx, sizeof(pEntry->szOSDEx), lpText, sizeof(pEntry->szOSDEx) - 1);	

										pMem->dwBusy = 0;
									}
								}
								else
									strncpy_s(pEntry->szOSDEx, sizeof(pEntry->szOSDEx), lpText, sizeof(pEntry->szOSDEx) - 1);	

							}
							else
								strncpy_s(pEntry->szOSD, sizeof(pEntry->szOSD), lpText, sizeof(pEntry->szOSD) - 1);

							pMem->dwOSDFrame++;

							bResult = TRUE;

							break;
						}
					}

					if (bResult)
						break;
				}
			}

			UnmapViewOfFile(pMapAddr);
		}

		CloseHandle(hMapFile);
	}

	return bResult;
}
//////////////////////////////////////////////////////////////////////
void CRTSSSharedMemoryInterface::ReleaseOSD(LPCSTR lpOSDOwner)
{
	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"RTSSSharedMemoryV2");

	if (hMapFile)
	{
		LPVOID pMapAddr = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		LPRTSS_SHARED_MEMORY pMem = (LPRTSS_SHARED_MEMORY)pMapAddr;

		if (pMem)
		{
			if ((pMem->dwSignature == 'RTSS') && 
				(pMem->dwVersion >= 0x00020000))
			{
				for (DWORD dwEntry=1; dwEntry<pMem->dwOSDArrSize; dwEntry++)
				{
					RTSS_SHARED_MEMORY::LPRTSS_SHARED_MEMORY_OSD_ENTRY pEntry = (RTSS_SHARED_MEMORY::LPRTSS_SHARED_MEMORY_OSD_ENTRY)((LPBYTE)pMem + pMem->dwOSDArrOffset + dwEntry * pMem->dwOSDEntrySize);

					if (!strcmp(pEntry->szOSDOwner, lpOSDOwner))
					{
						memset(pEntry, 0, pMem->dwOSDEntrySize);
						pMem->dwOSDFrame++;
					}
				}
			}

			UnmapViewOfFile(pMapAddr);
		}

		CloseHandle(hMapFile);
	}
}
//////////////////////////////////////////////////////////////////////
DWORD CRTSSSharedMemoryInterface::EmbedGraph(LPCSTR lpOSDOwner, DWORD dwOffset, FLOAT* lpBuffer, DWORD dwBufferPos, DWORD dwBufferSize, LONG dwWidth, LONG dwHeight, LONG dwMargin, FLOAT fltMin, FLOAT fltMax, DWORD dwFlags)
{
	DWORD dwResult	= 0;

	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"RTSSSharedMemoryV2");

	if (hMapFile)
	{
		LPVOID pMapAddr				= MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		LPRTSS_SHARED_MEMORY pMem	= (LPRTSS_SHARED_MEMORY)pMapAddr;

		if (pMem)
		{
			if ((pMem->dwSignature == 'RTSS') && 
				(pMem->dwVersion >= 0x00020000))
			{
				for (DWORD dwPass=0; dwPass<2; dwPass++)
					//1st pass : find previously captured OSD slot
					//2nd pass : otherwise find the first unused OSD slot and capture it
				{
					for (DWORD dwEntry=1; dwEntry<pMem->dwOSDArrSize; dwEntry++)
						//allow primary OSD clients (i.e. EVGA Precision / MSI Afterburner) to use the first slot exclusively, so third party
						//applications start scanning the slots from the second one
					{
						RTSS_SHARED_MEMORY::LPRTSS_SHARED_MEMORY_OSD_ENTRY pEntry = (RTSS_SHARED_MEMORY::LPRTSS_SHARED_MEMORY_OSD_ENTRY)((LPBYTE)pMem + pMem->dwOSDArrOffset + dwEntry * pMem->dwOSDEntrySize);

						if (dwPass)
						{
							if (!strlen(pEntry->szOSDOwner))
								strcpy_s(pEntry->szOSDOwner, sizeof(pEntry->szOSDOwner), lpOSDOwner);
						}

						if (!strcmp(pEntry->szOSDOwner, lpOSDOwner))
						{
							if (pMem->dwVersion >= 0x0002000c)
								//embedded graphs are supported for v2.12 and higher shared memory
							{
								if (dwOffset + sizeof(RTSS_EMBEDDED_OBJECT_GRAPH) + dwBufferSize * sizeof(FLOAT) > sizeof(pEntry->buffer))
									//validate embedded object offset and size and ensure that we don't overrun the buffer
								{
									UnmapViewOfFile(pMapAddr);

									CloseHandle(hMapFile);

									return 0;
								}

								LPRTSS_EMBEDDED_OBJECT_GRAPH lpGraph = (LPRTSS_EMBEDDED_OBJECT_GRAPH)(pEntry->buffer + dwOffset);
									//get pointer to object in buffer

								lpGraph->header.dwSignature	= RTSS_EMBEDDED_OBJECT_GRAPH_SIGNATURE;
								lpGraph->header.dwSize		= sizeof(RTSS_EMBEDDED_OBJECT_GRAPH) + dwBufferSize * sizeof(FLOAT);
								lpGraph->header.dwWidth		= dwWidth;
								lpGraph->header.dwHeight	= dwHeight;
								lpGraph->header.dwMargin	= dwMargin;
								lpGraph->dwFlags			= dwFlags;
								lpGraph->fltMin				= fltMin;
								lpGraph->fltMax				= fltMax;
								lpGraph->dwDataCount		= dwBufferSize;

								if (lpBuffer && dwBufferSize)
								{
									for (DWORD dwPos=0; dwPos<dwBufferSize; dwPos++)
									{
										FLOAT fltData = lpBuffer[dwBufferPos];

										lpGraph->fltData[dwPos] = (fltData == FLT_MAX) ? 0 : fltData;

										dwBufferPos = (dwBufferPos + 1) & (dwBufferSize - 1);
									}
								}

								dwResult = lpGraph->header.dwSize;
							}

							break;
						}
					}

					if (dwResult)
						break;
				}
			}

			UnmapViewOfFile(pMapAddr);
		}

		CloseHandle(hMapFile);
	}

	return dwResult;
}
//////////////////////////////////////////////////////////////////////
