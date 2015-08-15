#ifndef _INCLUDED_PLATFORM_H_
#define _INCLUDED_PLATFORM_H_

//////////////////////////////////////////////////////////////////////////
// Header files [DON"T SUPPORT UNICODE in this VERSION]
#include <windows.h>
#include <tchar.h>
#include <process.h>

#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

//////////////////////////////////////////////////////////////////////////
// UTILS and PLATFORM

#if (defined DEBUG || defined _DEBUG)
#define RASSERT(X) do{																\
	TCHAR szAssertMsg[256] = {0};													\
	sprintf(szAssertMsg, "Assertion Failed at: %s %d, retry it or ignore?", __FILE__, __LINE__);	\
    if(!(X)) { int mbRet = MessageBox(NULL, szAssertMsg, "ASSERTION FAILED", MB_YESNO | MB_APPLMODAL); \
if(IDYES == mbRet)	DebugBreak();}}	while(0)			
#else  //non debug
#define RASSERT(X)
#endif

//////////////////////////////////////////////////////////////////////////
// Lock implementation
class CriticalSection{
public:
	CriticalSection()	{	InitializeCriticalSection(&m_CriticalSection);	};
	~CriticalSection()	{	DeleteCriticalSection(&m_CriticalSection);		};
	void Enter()		{	EnterCriticalSection(&m_CriticalSection);		};
	void Leave()		{	LeaveCriticalSection(&m_CriticalSection);		};
//	BOOL Try()			{	TryEnterCriticalSection(&m_CriticalSection);	};

private:
	CRITICAL_SECTION m_CriticalSection;
};

//////////////////////////////////////////////////////////////////////////


#endif //_INCLUDED_PLATFORM_H_