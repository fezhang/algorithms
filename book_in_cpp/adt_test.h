#ifndef _INCLUDED_ADT_TEST_H_
#define _INCLUDED_ADT_TEST_H_

#include "datastructure_exercise.h"
#include "stack_use.h"
#include "queue_use.h"
#include "polynomial_use.h"
#include "simple_recursive_example.h"
#include "tree_use.h"

class adt_testee: public testee
{
public:
	virtual void execute();
	void check_sequence();
	void calc_math_expression();
	void test_fifo_interface();
	void test_polynomial_interface();
	void test_widgets_recursive();
	void test_tree_interface();
};

#endif //_INCLUDED_ADT_TEST_H_