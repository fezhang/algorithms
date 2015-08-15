#ifndef _INCLUDED_SIMPLE_RECURSIVE_EXAMPLE_H_
#define _INCLUDED_SIMPLE_RECURSIVE_EXAMPLE_H_

#include "platform.h"

class widgets_recursive
{
public:
	static int calc_prefix_expression(char* prefix, int& pos);
	static double calc_log_n_factorial(int n);
	
	template <typename Item>
	static Item get_max(Item a[], int l, int r)
	{
		if (l == r)
			return a[l];
		int m = (l+r)/2;
		Item u = get_max(a, l, m);
		Item v = get_max(a, m+1, r);
		if (u>v)
			return u;
		else
			return v;
	};

	static int hanoitower(int nLevel);
	static int fibonaci(int n);

protected:
	static int move_to_tower(int nLevel, int from, int to, int platform);
};

#endif //_INCLUDED_SIMPLE_RECURSIVE_EXAMPLE_H_