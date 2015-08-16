#ifndef _INCLUDED_STACK_USE_H_
#define _INCLUDED_STACK_USE_H_

#include "stack.hpp"

#define INVALID_MATH_RESULT 0XFFFFFFFF

class adt_stack_usage
{
public:
	static int calc_math_expression(char* input);

protected:	
	static DsBOOL infix_to_postfix(char* input, char* output);
	static int calc_postfix(char* input);
};
#endif //_INCLUDED_STACK_USE_H_