#ifndef _INCLUDED_CONNECTIVITY_H_
#define _INCLUDED_CONNECTIVITY_H_

#include "platform.h"

class union_find
{
public:
	union_find();
	virtual ~union_find();

	virtual void set_begin_end(const int begin, const int end);
	virtual int& get_begin();
	virtual int& get_end();
	virtual bool valid_pair(const int first, const int second);
	virtual void inseart_pair(const int first, const int second);
	virtual bool check_pair(const int first, const int second);
protected:
	int	m_begin;
	int m_end;
};

class connectivity
{
public:
	enum input_result{res_quit,res_ok, res_fail};
	connectivity();
	virtual ~connectivity();
public:
	virtual void set_union_find_object(union_find* uf);
	virtual void set_begin_end(const int& begin, const int& end);
	virtual bool check_object_is_valid();

	virtual void run();
	virtual input_result get_pair(int& first,  int& next);
	virtual void output_pair(const int& first, const int& next);
	virtual bool is_pair_exist(int& first, int& next);
protected:
	union_find*	m_union_find;
};


#endif //_INCLUDED_CONNECTIVITY_H_
