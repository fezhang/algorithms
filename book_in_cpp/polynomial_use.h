#ifndef _INCLUDED_POLYNOMIAL_USE_H_
#define _INCLUDED_POLYNOMIAL_USE_H_

#include "polynomial.hpp"

class adt_polynomial_usage
{
public:
	static void test_ctor_dtor();
	static void test_plus_minus();
	static void test_multiply();
	static void test_equal_notequal();
	static void test_evaluate();
};

#endif //_INCLUDED_POLYNOMIAL_USE_H_