#include "util.h"
#include <iostream>
using std::cout;
using std::endl;

//////////////////////////////////////////////////////////////////////////
// Implementation of class timer_mgr

timer_mgr* timer_mgr::m_instance = DsNULL;

timer_mgr* timer_mgr::get_mgr(int initLen)
{
	if(DsNULL == m_instance)
	{
		if(initLen <= 10)
			initLen = 10;
		m_instance = new timer_mgr(initLen);
		return m_instance;
	}
	else
		return m_instance;
};

void timer_mgr::free_mgr()
{
	if(DsNULL != m_instance)
	{
		delete m_instance;
		m_instance = DsNULL;
	}
};

timer_mgr::~timer_mgr()
{
	if(m_strArray)
	{
		for(int i=0; i<m_used; ++i)
		{
			delete[] m_strArray[i];
		}
		delete[] m_strArray;
	}
	if(m_timerArray)
		delete[] m_timerArray;
	m_strArray = DsNULL;
	m_timerArray = DsNULL;
};

void timer_mgr::clear()
{
	if(m_strArray)
	{
		for(int i=0; i<m_used; ++i)
		{
			delete[] m_strArray[i];
		}
	}
	m_used = 0;
};

void timer_mgr::output()
{
	if(m_strArray && m_timerArray)
	{
		for(int i=0; i<m_used; ++i)
		{
			cout<<"When "<<m_strArray[i]<<" Time len= "<<m_timerArray[i]<<endl;
		}
		if(0 == m_used)
			cout<<"There is no timer data here!"<<endl;
	}
	else
		cout<<"There is no timer data here!"<<endl;
};

void timer_mgr::add_item(char* str, int len)
{
	if(m_used == m_len-1)
	{
		cout<<"Issue! No more spaces for add timer items!"<<endl;
		return;
	}

	int nStrLen = strlen(str);
	if(!nStrLen)
	{
		m_strArray[m_used] = new char[10];
		lstrcpyn(m_strArray[m_used], "NULL", 5);
	}
	else
	{
		m_strArray[m_used] = new char[nStrLen+5];
		lstrcpyn(m_strArray[m_used], str, nStrLen+1);
	}
	m_timerArray[m_used] = len;
	++m_used;
};

timer_mgr::timer_mgr(int initLen)
{
	m_strArray = new char*[initLen];
	m_timerArray = new int[initLen];
	m_len = initLen;
	m_used = 0;
	if(m_strArray && m_timerArray)
	{
		for(int i=0; i<m_len; ++i)
		{
			m_strArray[i] = DsNULL;
			m_timerArray[i] = 0;
		}
	}
};
	
#ifdef _DEBUG
BOOL output_control::m_bPrintCtorDtor = FALSE;
BOOL output_control::m_bPrintFunc = FALSE;
#else
BOOL output_control::m_bPrintCtorDtor = FALSE;
BOOL output_control::m_bPrintFunc = FALSE;
#endif
// End class timer_mgr
//////////////////////////////////////////////////////////////////////////