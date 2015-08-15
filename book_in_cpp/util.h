#ifndef _INCLUDED_UTIL_H_
#define _INCLUDED_UTIL_H_

#include "ds_comm.h"

typedef void (*pfTimerCallBack)(void* param);

class timer{
public:
	timer()
	{
		QueryPerformanceCounter(&m_llStartTime);
	};
	~timer()
	{
	};

	static __int64 GetPerformanceFrequency()
	{
		LARGE_INTEGER pf;
		QueryPerformanceFrequency(&pf);
		return pf.QuadPart;
	};

	__int64 Interval(){
		LARGE_INTEGER currTime;
		QueryPerformanceCounter(&currTime);
		return currTime.QuadPart - m_llStartTime.QuadPart;
	};

	void Reset(){
		QueryPerformanceCounter(&m_llStartTime);
	};
protected:
	LARGE_INTEGER	m_llStartTime;
};

class timer_mgr
{
public:
	static timer_mgr* get_mgr(int initLen=-1);
	static void free_mgr();
	virtual ~timer_mgr();

	void clear();
	void output();
	void add_item(char*, int len);
protected:
	timer_mgr(int initLen);
	static timer_mgr*	m_instance;
	char**	m_strArray;
	int*	m_timerArray;
	int		m_len;
	int		m_used;
};

template <typename T>
void Exchange(T& item1, T& item2)
{
	T temp = item1;
	item1 = item2;
	item2 = temp;
}

#include <time.h>
#include <stdlib.h>

class rand_generator
{
public:
	rand_generator(UINT32 seed, int start, int end)
	{ 
		if(seed==0)
		{
			srand((UINT32)time(NULL));
		}
		else
			srand(seed);

		if(start>end)
			Exchange(start, end);

		m_nStart = start;
		m_nEnd = end;
	};

	int	get()
	{
		return m_nStart+rand()%(m_nEnd-m_nStart+1);
	};

	virtual ~rand_generator(){};
protected:
	int		m_nStart;
	int		m_nEnd;
};

class output_control
{
public:
	static BOOL m_bPrintCtorDtor;
	static BOOL m_bPrintFunc;
};

#define OUT_CD(exp)	\
	if(output_control::m_bPrintCtorDtor)	\
		exp;

#define OUT_FU(exp)	\
	if(output_control::m_bPrintFunc)	\
		exp;

#endif //_INCLUDED_UTIL_H_