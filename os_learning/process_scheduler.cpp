#include "process_scheduler.h"
#include "os_base.h"

bool g_bTerminate = FALSE;

CProcessScheduler::CProcessScheduler()
    :m_processRunning(NULL),
    m_nRunForApp(0),
    m_nIdle(0)
{
};

CProcessScheduler::~CProcessScheduler()
{
};

void CProcessScheduler::HeartBeat()
{
	if(g_bTerminate)
		return;

  //  OutputStatus();
    ScanWaittingVector();

	if(m_processRunning)
	{
        if(m_processRunning->complete())
        {
            TerminateProcess(m_processRunning);
		    AddCompleteProcess(m_processRunning);

            ExecNextProcess();
        }
        else if(m_processRunning->go_waitting())
        {
		    TerminateProcess(m_processRunning);
		    AddWaittingProcess(m_processRunning);

            ExecNextProcess();
        }
        else
            ExecuteProcess(m_processRunning);
	}
    else
        ExecNextProcess();
};

void CProcessScheduler::ExecuteProcess(IProcess* pProcess)
{
	if(pProcess)
    {
        pProcess->decreace_slice();
		pProcess->start();
        ++m_nRunForApp;
    }
};

void CProcessScheduler::TerminateProcess(IProcess* pProcess)
{
	if(pProcess)
		pProcess->stop();
};

void CProcessScheduler::AddReadyProcess(IProcess* pProcess)
{
	if(pProcess)
		m_queueReady.put(pProcess);
};

void CProcessScheduler::AddWaittingProcess(IProcess* pProcess)
{
	if(pProcess)
    {
        pProcess->set_waitting_time(pProcess->get_last_allocated());	
        m_vectorWaitting.push_back(pProcess);
    }
};

void CProcessScheduler::AddCompleteProcess(IProcess* pProcess)
{
    if(pProcess)
    {
        cout<<"!!! process "<<pProcess->get_pid()<<" complete!"<<endl;
		m_queueComplete.put(pProcess);
    }
};

/*static*/ void APIENTRY CProcessScheduler::OSAPC(
		LPVOID lpArgToCompletionRoutine,
		DWORD dwTimerLowValue,
		DWORD dwTimerHighValue
		)
{
	CProcessScheduler* pScheduler = (CProcessScheduler*)lpArgToCompletionRoutine;

	if(!pScheduler)
		return;
	
	pScheduler->HeartBeat();
};

void CProcessScheduler::TerminateKernel()
{
	if(m_processRunning)
	{
		TerminateProcess(m_processRunning);
		m_processRunning = NULL;
	}
	g_bTerminate = TRUE;

    cout<<"total run for applicate is:"<<m_nRunForApp<<endl;
    cout<<"total idle is:"<<m_nIdle<<endl;
};

void CProcessScheduler::ScanWaittingVector()
{
    IProcess* pTemp = NULL;
    for(int i=0; i<m_vectorWaitting.size();)
    {
        pTemp = m_vectorWaitting[i];
        if(pTemp && pTemp->waitting_complete())
        {
            m_queueReady.put(pTemp);
            m_vectorWaitting.remove(i);
        }
        else
            ++i;
    };
};

void CProcessScheduler::ExecNextProcess()
{
    m_processRunning = NULL;
    IProcess* pNextRunningProcess = m_queueReady.get();
	if(pNextRunningProcess)
	{
	    m_processRunning = pNextRunningProcess;
        m_processRunning->allocate_timer();
	    ExecuteProcess(m_processRunning);
	}
    else
    {
        if(!m_queueReady.empty() || m_vectorWaitting.size()!=0)
        {
            ++m_nIdle;
            cout<<"idle"<<endl;
        }
    }
};

void CProcessScheduler::OutputStatus()
{
    cout<<"waitting size="<<m_vectorWaitting.size()
        <<" ready queue is empty="<<m_queueReady.empty()<<endl;
};
//////////////////////////////////////////////////////////////////////////
		
/*static*/ void COSHeartBeat::kernel_start(CProcessScheduler* pScheduler)
{
	if(!s_pWaitableTimer)
	{
		s_pWaitableTimer = new CWaitableTimer("system kernel timer");
		if(s_pWaitableTimer)
			s_pWaitableTimer->SetWaitableTimer(100, CProcessScheduler::OSAPC, pScheduler);
	}

	while(!g_bTerminate)
	{
		SleepEx(INFINITE, TRUE);
	}
};

/*static*/ void COSHeartBeat::kernel_end()
{
	if(s_pWaitableTimer)
	{
		delete s_pWaitableTimer;
		s_pWaitableTimer = NULL;
	}
};

/*static*/ CWaitableTimer* COSHeartBeat::s_pWaitableTimer = NULL;

//////////////////////////////////////////////////////////////////////////

CWinEvent::CWinEvent(char* strName)
:m_hEvent(INVALID_HANDLE_VALUE)
{
	m_hEvent = CreateEvent(NULL, TRUE, FALSE, strName);
};

CWinEvent::~CWinEvent()
{
	if(m_hEvent)
	{
		CloseHandle(m_hEvent);
		m_hEvent = INVALID_HANDLE_VALUE;
	}
};

BOOL CWinEvent::SetEvent()
{
	if(INVALID_HANDLE_VALUE == m_hEvent)
		return FALSE;

	return ::SetEvent(m_hEvent);
};

BOOL CWinEvent::ResetEvent()
{
	if(INVALID_HANDLE_VALUE == m_hEvent)
		return FALSE;

	return ::ResetEvent(m_hEvent);
};

HANDLE CWinEvent::GetHandle()
{
	return m_hEvent;
};
//////////////////////////////////////////////////////////////////////////
/*static*/ void CKernelEvent::init()
{
	if(!m_pEventTerminate)
		m_pEventTerminate = new CWinEvent("event terminate system");
};

/*static*/ void CKernelEvent::term()
{
	if(m_pEventTerminate)
	{
		delete m_pEventTerminate;
		m_pEventTerminate = NULL;
	}
};
/*static*/ void CKernelEvent::SetTerminateEvent()
{
	if(m_pEventTerminate)
		m_pEventTerminate->SetEvent();
};

/*static*/ void CKernelEvent::ResetTerminateEvent()
{
	if(m_pEventTerminate)
		m_pEventTerminate->ResetEvent();
};

/*static*/ CWinEvent* CKernelEvent::m_pEventTerminate = NULL;

/*static*/ HANDLE CKernelEvent::GetTerminateHandle()
{
	return m_pEventTerminate->GetHandle();
};

//////////////////////////////////////////////////////////////////////////
