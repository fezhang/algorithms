#ifndef _INCLUDED_LIST_HPP_
#define _INCLUDED_LIST_HPP_

#include "platform.h"
#include "obj_interface.hpp"

template <typename Item>	class list_node_single;
template <typename Item>	class list_node_double;
template <typename Item>	class list_single;
template <typename Item>	class list_double;

template <typename Item>
class list_node_single{
public:
	list_node_single():
		m_pNext(DsNULL){};
	list_node_single(Item& data, list_node_single<Item>* pNext=DsNULL):
		m_pNext(pNext), m_data(data){};
	virtual ~list_node_single() {};

	list_node_single<Item>* get_next()
		{ return m_pNext;};
	Item& get_data()
		{ return m_data;};
	
	void set_next(list_node_single<Item>* pNext)
		{ m_pNext = pNext;};
	void set_data(Item& data)
		{ m_data = data;};

protected:
	Item					m_data;
	list_node_single<Item>*	m_pNext;
};

template <typename Item>
class list_node_double{
public:
	list_node_double():
		m_pNext(DsNULL),m_pPrev(DsNULL){};
	list_node_double(Item& data, list_node_double<Item>* pNext=DsNULL, list_node_double<Item>* pPrev=DsNULL):
		m_pNext(pNext), m_data(data), m_pPrev(pPrev){};
	virtual ~list_node_double() {};

	list_node_double<Item>* get_next()
		{ return m_pNext;};
	list_node_double<Item>* get_prev()
		{ return m_pPrev;};
	Item& get_data()
		{ return m_data;};
	
	void set_next(list_node_double<Item>* pNext)
		{ m_pNext = pNext;};
	void set_prev(list_node_double<Item>* pPrev)
		{ m_pPrev = pPrev;};
	void set_data(Item& data)
		{ m_data = data;};

protected:
	Item					m_data;
	list_node_double<Item>*	m_pNext;
	list_node_double<Item>*	m_pPrev;
};

template <typename Item>	
class list_single
{
public:
	typedef list_node_single<Item>		t_node;
	typedef list_node_single<Item>*		t_pnode;

public:
	list_single();
	virtual ~list_single();
	
public:
	void add(Item);
	void remove(Item);
	void clear_all();
	
	int	size();
	t_pnode get_head();
	void set_head(t_pnode newHead);

protected:
	list_single& operator=(list_single&);
	list_single(list_single<Item>&);
	t_pnode m_head;
	int		m_nCount;
};

template <typename Item>
list_single<Item>::list_single()
:m_head(DsNULL),m_nCount(0)
{
};

template <typename Item>
list_single<Item>::~list_single()
{
	clear_all();
};
	
template <typename Item>
void list_single<Item>::add(Item it)
{
	list_node_single<Item>* pNewHead = new
		list_node_single<Item>(it);
	if(pNewHead)
	{
		pNewHead->set_next(m_head);
		m_head = pNewHead;
		++m_nCount;
	}
};

template <typename Item>
void list_single<Item>::remove(Item it)
{
	list_node_single<Item>* pPos = m_head;
	if(!pPos)
		return;

	if(m_head->get_data() == it)
	{//remove head
		m_head = m_head->get_next();
		delete pPos;
		pPos = DsNULL;
		--m_nCount;
		return;
	}

	while(pPos->get_next())
	{
		if(pPos->get_next()->get_data() == it)
		{//remove this node
			list_node_single<Item>* pToBeDeleted = 
				pPos->get_next();
			pPos->get_next() = pToBeDeleted->get_next();
			delete pToBeDeleted;
			pToBeDeleted = DsNULL;
			--m_nCount;
			return;
		}
		pPos = pPos->get_next();
	}
	return;
};

template <typename Item>
void list_single<Item>::clear_all()
{
	list_node_single<Item>* pToBeDeleted = NULL;
	while(m_head)
	{
		pToBeDeleted = m_head;
		m_head = m_head->get_next();
		delete pToBeDeleted;
		pToBeDeleted = NULL;
	}
};

template <typename Item>	
int	list_single<Item>::size()
{
	return m_nCount;
};

template <typename Item>
list_node_single<Item>* list_single<Item>::get_head()
{
	return m_head;
};

template <typename Item>
void list_single<Item>::set_head(list_node_single<Item>* newHead)
{
	m_head = newHead;
};

template <typename Item>	
class list_double
{
public:
	typedef list_node_double<Item>		t_node;
	typedef list_node_double<Item>*		t_pnode;

public:
	enum {BIG_TO_SMALL=0, SMALL_TO_BIG, NO_ARRANGEMENT};
	list_double(int arrangeType = NO_ARRANGEMENT);
	list_double(list_double<Item>&);
	virtual ~list_double();
	list_double& operator=(list_double&);

public:
	void add(Item);
	void remove(Item);
	void clear_all();
	
	int	count();
protected:
	t_pnode m_head;
	t_pnode m_tail;
	int		m_nCount;
};
#endif //_INCLUDED_LIST_HPP_