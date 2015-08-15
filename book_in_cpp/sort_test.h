#ifndef _INCLUDED_SORT_TEST_H_
#define _INCLUDED_SORT_TEST_H_

#include "elementary_sort_frame.h"

class sort_testee: public testee
{
public:
	virtual void execute();
	void test_element_sort();
};
#endif //_INCLUDED_SORT_TEST_H_