#include "process_scheduler.h"
#include "os_base.h"

#include <iostream>
using namespace std;

class MyProcess: public IProcess
{
public:
	MyProcess(int id,int time):IProcess(time),m_id(id){
        cout<<"id = "<<id<<" time = "<<time<<endl;
    };
	virtual ~MyProcess(){};
	void start(){cout<<"start "<<m_id<<endl;};
	void stop(){cout<<"end "<<m_id<<endl;};
    virtual int get_pid(){ return m_id;};
protected:
	int m_id;
};

DWORD WINAPI OSKernelThread(LPVOID);

int main()
{
	CProcessScheduler ps;

	DWORD dwThreadID = 0;
	HANDLE hKernelTread =
		CreateThread(NULL, 0, OSKernelThread, &ps, NULL, &dwThreadID);

    rand_generator rg(4,30);
    IProcess* arrProcess[100];
    int i=0;
    int nProcessCount = 10;
    for(i=0; i<nProcessCount; ++i)
    {
        Sleep(500);
        arrProcess[i] = new MyProcess(i, rg.get());
        ps.AddReadyProcess(arrProcess[i]);
    }
	
	Sleep(1000000);
	ps.TerminateKernel();
	
	WaitForSingleObject(hKernelTread, INFINITE);
	CloseHandle(hKernelTread);

	for(i=0; i<nProcessCount; ++i)
    {
        delete arrProcess[i];
    }

	return 0;
}

DWORD WINAPI OSKernelThread(LPVOID ps)
{
	COSHeartBeat::kernel_start((CProcessScheduler*)ps);
	COSHeartBeat::kernel_end();
	return 0;
};