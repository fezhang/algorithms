#ifndef _INCLUDED_TASK_SCHEDULER_H_
#define _INCLUDED_TASK_SCHEDULER_H_

#include "waitable_timer.h"
#include "queue.hpp"
#include "vector.hpp"

class IProcess;

class CProcessScheduler;
class COSHeartBeat;
class CKernelEvents;
class CWinEvent;

class CProcessScheduler
{
public:
	CProcessScheduler();
	virtual ~CProcessScheduler();
	
	void HeartBeat();
	void ExecuteProcess(IProcess*);
	void TerminateProcess(IProcess*);
	
	static void APIENTRY OSAPC(
		LPVOID lpArgToCompletionRoutine,
		DWORD dwTimerLowValue,
		DWORD dwTimerHighValue
		);

	void TerminateKernel();
	void AddReadyProcess(IProcess*);
	void AddWaittingProcess(IProcess*);
    void AddCompleteProcess(IProcess*);

protected:
    void ScanWaittingVector();
    void ExecNextProcess();
    void OutputStatus();

private:
	IProcess*						m_processRunning;
	queue_array<IProcess*>	        m_queueReady;
	queue_array<IProcess*>	        m_queueComplete;
    _vector<IProcess*>              m_vectorWaitting;
    int                             m_nRunForApp;
    int                             m_nIdle;
};

class COSHeartBeat
{
public:
	static void kernel_start(CProcessScheduler*);
	static void kernel_end();

private:
	static CWaitableTimer* s_pWaitableTimer;
};

class CWinEvent
{
public:
	CWinEvent(char* strName);
	virtual ~CWinEvent();
	BOOL SetEvent();
	BOOL ResetEvent();
	HANDLE GetHandle();

private:
	HANDLE m_hEvent;
};

class CKernelEvent
{
public:
	static void init();
	static void term();

	static void SetTerminateEvent();
	static void ResetTerminateEvent();
	static HANDLE GetTerminateHandle();
private:
	static CWinEvent* m_pEventTerminate;
};
#endif //_INCLUDED_TASK_SCHEDULER_H_