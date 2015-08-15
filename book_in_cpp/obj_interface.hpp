#ifndef _INCLUDED_OBJECT_INTERFACES_HPP_
#define _INCLUDED_OBJECT_INTERFACES_HPP_

#include "platform.h"

template <typename T1, typename T3>
struct uni_function
{
	typedef T1 argument_type;
	typedef T3 result_type;
};

template <typename T1, typename T2, typename T3>
struct bin_function
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef T3 result_type;
};

// operators +,-,*,/,>,>=,<,<=,==,!=
template <typename T>
struct op_plus: public bin_function<T, T, T>
{
	T operator()(const T& _X, const T& _Y)const
	{
		return (_X+_Y);
	}
};

template <typename T>
struct op_minus: public bin_function<T, T, T>
{
	T operator()(const T& _X, const T& _Y)const
	{
		return (_X-_Y);
	}
};

template <typename T>
struct op_multi: public bin_function<T, T, T>
{
	T operator()(const T& _X, const T& _Y)const
	{
		return (_X*_Y);
	}
};

template <typename T>
struct op_divides: public bin_function<T, T, T>
{
	T operator()(const T& _X, const T& _Y)const
	{
		return (_X/_Y);
	}
};

template <typename T>
struct op_great: public bin_function<T, T, BOOL>
{
	BOOL operator()(const T& _X, const T& _Y)const
	{
		return (_X>_Y);
	}
};

template <typename T>
struct op_great_equal: public bin_function<T, T, BOOL>
{
	BOOL operator()(const T& _X, const T& _Y)const
	{
		return (_X>=_Y);
	}
};

template <typename T>
struct op_less: public bin_function<T, T, BOOL>
{
	BOOL operator()(const T& _X, const T& _Y)const
	{
		return (_X<_Y);
	}
};

template <typename T>
struct op_less_equal: public bin_function<T, T, BOOL>
{
	BOOL operator()(const T& _X, const T& _Y)const
	{
		return (_X<=_Y);
	}
};

template <typename T>
struct op_equal: public bin_function<T, T, BOOL>
{
	BOOL operator()(const T& _X, const T& _Y)const
	{
		return (_X==_Y);
	}
};

template <typename T>
struct op_not_equal: public bin_function<T, T, BOOL>
{
	BOOL operator()(const T& _X, const T& _Y)const
	{
		return (_X!=_Y);
	}
};

template <typename Item>
int find(Item* pArr, Item& it, int nArrLen)
{
	int nIndex = -1;
	if(!pArr || nArrLen<=0)
		return nIndex;
	for(int i=0; i<nArrLen; ++i)
	{
		if(pArr[i] == it)
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}
#endif //_INCLUDED_OBJECT_INTERFACES_HPP_