#ifndef _INCLUDED_TEST_FRAME_H_
#define _INCLUDED_TEST_FRAME_H_

#include "typedef.h"
#include "ds_comm.h"

class tester;
class testee;

class tester
{
public:
	tester();
	virtual ~tester();
	void set_testee(testee*);
	void clear_testee();
	virtual void run();
private:
	testee*	m_ptee;
};

class testee
{
public:
	virtual void execute() = 0;
};

#endif //_INCLUDED_TEST_FRAME_H_