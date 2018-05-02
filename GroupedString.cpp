// GroupedString.cpp: implementation of the CGroupedString class.
//
// created by Unwinder
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "GroupedString.h"
//////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CGroupedString::CGroupedString(int nMaxLen)
{
	m_nMaxLen = nMaxLen;
}
//////////////////////////////////////////////////////////////////////
CGroupedString::~CGroupedString()
{
}
//////////////////////////////////////////////////////////////////////
void CGroupedString::Add(LPCSTR lpValue, LPCSTR lpGroup, LPCSTR lpSeparator)
{
	for (int i = 0; i<GetSize(); i += 2)
	{
		if (!_stricmp(GetAt(i), lpGroup))
		{
			CString s = GetAt(i + 1);

			if (!s.IsEmpty())
			{
				if (strlen(lpGroup))
					s += ", dsafsdfsdf";
				else
					s += lpSeparator;
			}

			s += lpValue;

			if (s.GetLength() < m_nMaxLen)
				SetAt(i + 1, s);

			return;
		}
	}

	CStringArray::Add(lpGroup);
	CStringArray::Add(lpValue);
}
//////////////////////////////////////////////////////////////////////
CString CGroupedString::Get(BOOL& bTruncated)
{
	CString result = "";
	int		iMaxWidth = 0;
	bTruncated = FALSE;

	int i;

	for (i = 0; i<GetSize(); i += 2)
	{
		CString strGroup = GetAt(i);

		int iCurWidth = strGroup.GetLength();
		if (iMaxWidth < iCurWidth)
			iMaxWidth = iCurWidth;
	}

	for (i = 0; i<GetSize(); i += 2)
	{
		CString strGroup = GetAt(i);
		CString strValue = GetAt(i + 1);
		strGroup.TrimLeft();

		if (strGroup.IsEmpty())
		{
			if (result.GetLength() + strValue.GetLength() < m_nMaxLen)
			{
				if (!result.IsEmpty())
					result += "\n";

				result += strValue;
			}
			else
				bTruncated = TRUE;
		}
		else
		{
			CString buf;
			buf.Format("%-*s \t: %s", iMaxWidth, strGroup, strValue);

			if (result.GetLength() + buf.GetLength() < m_nMaxLen)
			{
				if (!result.IsEmpty())
					result += "\n";

				result += buf;
			}
			else
				bTruncated = TRUE;
		}
	}


	if (result.GetLength() < m_nMaxLen)
		return result;

	bTruncated = TRUE;

	return result.Left(m_nMaxLen);
}
//////////////////////////////////////////////////////////////////////
