#ifndef _INCLUDED_DATA_STRUCTURE_EXERCISE_H_
#define _INCLUDED_DATA_STRUCTURE_EXERCISE_H_

#include "platform.h"

class adt_stack_exercise
{
public:
	// in book: page 147, e4.11
	// please ref book
	// this version hasn't considered the same char in sequence
	// and also ignore the wrong input
	static DsBOOL check_squence(char* input, char* output);
	static int get_char_index(char* str, char ch);
};
#endif //_INCLUDED_DATA_STRUCTURE_EXERCISE_H_