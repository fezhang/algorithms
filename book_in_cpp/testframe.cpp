#include "testframe.h"
#include <iostream>
using namespace std;

tester::tester()
:m_ptee(DsNULL){
};

tester::~tester()
{
	m_ptee = DsNULL;
};

void tester::set_testee(testee* tee)
{
	m_ptee = tee;
};

void tester::clear_testee()
{
	set_testee(DsNULL);
};

void tester::run()
{
	if(DsNULL != m_ptee)
		m_ptee->execute();
	else
		cout<<"There is no testee here! To test please set a testee first!"<<endl;
};
