#ifndef _INCLUDED_WAITABLE_TIMER_H_
#define _INCLUDED_WAITABLE_TIMER_H_

#include <windows.h>

typedef void (APIENTRY *pfAPC)(
    LPVOID lpArgToCompletionRoutine,
    DWORD dwTimerLowValue,
    DWORD dwTimerHighValue
    );

typedef HANDLE (WINAPI *pfCreateWaitableTimer)(
	LPSECURITY_ATTRIBUTES,
	BOOL,
	LPCTSTR);

typedef BOOL (WINAPI *pfSetWaitableTimer)(
	HANDLE,
	const LARGE_INTEGER *,
	LONG,
	pfAPC,
	LPVOID, 
	BOOL);

class CWaitableTimer
{
public:
	CWaitableTimer(char* strName);
	virtual ~CWaitableTimer();
	
	//fail, return FALSE, success, return NONZERO
	BOOL SetWaitableTimer(LONG, pfAPC, LPVOID);

protected:
	HANDLE					m_hWaitableTimer;
	pfCreateWaitableTimer	m_pfCreate;
	pfSetWaitableTimer		m_pfSet;
};
#endif //_INCLUDED_WAITABLE_TIMER_H_