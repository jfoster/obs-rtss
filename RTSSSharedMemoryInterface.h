// RTSSSharedMemoryInterface.h: interface for the CRTSSSharedMemoryInterface class.
//
// created by Unwinder
//////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////
#include <RTSSSharedMemory.h>
//////////////////////////////////////////////////////////////////////
class CRTSSSharedMemoryInterface
{
public:
	CRTSSSharedMemoryInterface();
	virtual ~CRTSSSharedMemoryInterface();

	BOOL	UpdateOSD(LPCSTR lpOSDOwner, LPCSTR lpText);
		//connects to RTSS shared memory and copies lpText to OSD text slot owned by our application, 

		//NOTE: this function captues OSD text slot if we don not own one yet
	void	ReleaseOSD(LPCSTR lpOSDOwner);
		//connects to RTSS shared memory and releases OSD text slot owned by our application
	DWORD	EmbedGraph(LPCSTR lpOSDOwner, DWORD dwOffset, FLOAT* lpBuffer, DWORD dwBufferPos, DWORD dwBufferSize, LONG dwWidth, LONG dwHeight, LONG dwMargin, FLOAT fltMin, FLOAT fltMax, DWORD dwFlags);
		//connects to RTSS shared memory and embeds new graph into object buffer of OSD text slot owned by our application, returns modified object buffer position

		//NOTE: this function captues OSD text slot if we don not own one yet
};
//////////////////////////////////////////////////////////////////////
