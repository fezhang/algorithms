#ifndef _INCLUDED_UNION_FIND_H_
#define _INCLUDED_UNION_FIND_H_

#include "connectivity.h"

class uf_array: public union_find
{
public:
	uf_array();
	virtual ~uf_array();

	virtual void set_begin_end(const int begin, const int end);
	virtual void inseart_pair(const int first, const int second);
	virtual bool check_pair(const int first, const int second);
	void DUMP();
protected:
	int*	m_base;
	int		m_len;
};

class uf_quick_tree: public union_find
{
public:
	uf_quick_tree();
	virtual ~uf_quick_tree();

	virtual void set_begin_end(const int begin, const int end);
	virtual void inseart_pair(const int first, const int second);
	virtual bool check_pair(const int first, const int second);
	void DUMP();
protected:
	int*	m_base;
	int		m_len;
};

class uf_weight_tree: public union_find
{
public:
	uf_weight_tree();
	virtual ~uf_weight_tree();

	virtual void set_begin_end(const int begin, const int end);
	virtual void inseart_pair(const int first, const int second);
	virtual bool check_pair(const int first, const int second);
protected:
	int*	m_base;
	int*	m_weight;
	int		m_len;
};

class uf_compression_weight_tree: public uf_weight_tree
{
public:
	uf_compression_weight_tree();
	virtual ~uf_compression_weight_tree();

	virtual bool check_pair(const int first, const int second);
};
#endif //_INCLUDED_UNION_FIND_H_
