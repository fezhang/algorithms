#ifndef _INCLUDED_OPERATING_SYSTEM_BASE_H_
#define _INCLUDED_OPERATING_SYSTEM_BASE_H_

#include "util.h"

class IProcess
{
public:
    IProcess(int nTime)
        :m_nTotalTime(nTime),
        m_nLastAllocated(2),
        m_nAllocatedTime(2)
    {};
    virtual ~IProcess(){};

    void decreace_slice(){
        --m_nAllocatedTime;
        --m_nTotalTime;
    };
    bool complete(){
        if(m_nTotalTime == 0)
            return true;
        return false;
    };
    bool go_waitting(){
        if(0 >= m_nAllocatedTime)
            return true;
        return false;
    };
    void allocate_timer(){
        m_nLastAllocated *= 2;
        m_nAllocatedTime = m_nLastAllocated;
    };
    void set_waitting_time(int nTime){
        m_nWaittingTime = nTime;
    };
    bool waitting_complete(){
        return (--m_nWaittingTime <= 0);
    };
    int get_last_allocated(){
        return m_nLastAllocated;
    };

	virtual void start() = 0;
	virtual void stop() = 0;
    virtual int get_pid() = 0;
protected:
    int m_nTotalTime;
    int m_nLastAllocated;
    int m_nAllocatedTime;
    int m_nWaittingTime;
};
#endif //_INCLUDED_OPERATING_SYSTEM_BASE_H_