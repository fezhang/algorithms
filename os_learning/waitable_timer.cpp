#include "waitable_timer.h"

CWaitableTimer::CWaitableTimer(char* strName)
:m_hWaitableTimer(INVALID_HANDLE_VALUE),
m_pfCreate(NULL),
m_pfSet(NULL)
{
	HINSTANCE hKernel32 = ::GetModuleHandle("kernel32.dll");
	if(NULL == hKernel32)
		return;

#ifdef UNICODE
	m_pfCreate =	(pfCreateWaitableTimer)GetProcAddress(hKernel32, "CreateWaitableTimerW");	
#else
	m_pfCreate =	(pfCreateWaitableTimer)GetProcAddress(hKernel32, "CreateWaitableTimerA");
#endif

	m_pfSet =		(pfSetWaitableTimer)GetProcAddress(hKernel32, "SetWaitableTimer");
	
	if(!m_pfCreate || !m_pfSet)
	{
		return;
	}

	m_hWaitableTimer = m_pfCreate(NULL, TRUE, strName);
};

CWaitableTimer::~CWaitableTimer()
{
	if(m_hWaitableTimer != INVALID_HANDLE_VALUE)
		::CloseHandle(m_hWaitableTimer);
};
	
BOOL CWaitableTimer::SetWaitableTimer(LONG nInterval, 
									  pfAPC _pfAPC, LPVOID pParam)
{
	BOOL bRet = FALSE;

	if(INVALID_HANDLE_VALUE == m_hWaitableTimer || !m_pfSet)
		return bRet;

    LARGE_INTEGER liDueTime;

    liDueTime.QuadPart=-10000000;

	bRet = m_pfSet(
		m_hWaitableTimer,
		&liDueTime,
		nInterval,
		_pfAPC,
		pParam,
		FALSE);

	return bRet;
};
