#ifndef _INCLUDED_QUEUE_HPP_
#define _INCLUDED_QUEUE_HPP_

#include "list.hpp"

// classes in this file
template <typename Item>	class iqueue;
template <typename Item>	class queue_array;
template <typename Item>	class queue_list_double;
template <typename Item>	class queue_list_single;

template <typename Item>
class iqueue
{
public:
	iqueue(){};
	virtual ~iqueue(){};
	virtual BOOL empty() const = 0;
	virtual BOOL full() const { return FALSE;}; //default implemention said queue will not full
	virtual void put(Item item) = 0;
	virtual Item get() = 0;
};

template <typename Item>
class queue_array: public iqueue<Item>
{
public:
	enum{SIZE_INIT=32};
	queue_array();
	queue_array(int nInitlen);
	virtual ~queue_array();
	virtual BOOL empty() const;
	virtual BOOL full() const;
	virtual void put(Item item);
	virtual Item get();
protected:
	Item*	m_pBase;
	int		m_nBuffLen;
	int		m_nDataLen;
	int		m_posHead;
	int		m_posTail;
};

template <typename Item>
queue_array<Item>::queue_array()
{
	m_posHead = 0;
	m_posTail = 0;
	m_nBuffLen = 0;
	m_nDataLen = 0;
	m_pBase = new Item[queue_array<Item>::SIZE_INIT];
	if(m_pBase)
	{
		m_nBuffLen = queue_array<Item>::SIZE_INIT;
	}
}

template <typename Item>
queue_array<Item>::queue_array(int nInitlen)
{
	m_posHead = 0;
	m_posTail = 0;
	m_nBuffLen = 0;
	m_nDataLen = 0;
	m_pBase = new Item[nInitlen];
	if(m_pBase)
	{
		m_nBuffLen = nInitlen;
	}
}

template <typename Item>
queue_array<Item>::~queue_array()
{
	if(m_pBase)
		delete[] m_pBase;
}

template <typename Item>
BOOL queue_array<Item>::empty() const
{
	if(m_nDataLen == 0)
		return TRUE;
	else
		return FALSE;
};

template <typename Item>
BOOL queue_array<Item>::full() const
{
	if(m_nDataLen == m_nBuffLen)
		return TRUE;
	else
		return FALSE;
};

template <typename Item>
void queue_array<Item>::put(Item item)
{
	if(full())
	{
		cout<<"Error in queue_array::put, buff is not enough!"<<endl;
		return;
	}
	m_pBase[m_posHead] = item;
	m_nDataLen += 1;
	m_posHead = (m_posHead+1)%m_nBuffLen;
};

template <typename Item>
Item queue_array<Item>::get()
{
	Item iRet = 0;
	if(!empty())
	{
		iRet = m_pBase[m_posTail];
		m_nDataLen -= 1;
		m_posTail = (m_posTail+1)%m_nBuffLen;
	}
//	else
//	{
//		cout<<"Error in queue_array::get, there is no data here!"<<endl;
//	}
	return iRet;
};

template <typename Item>
class queue_list_double: public iqueue<Item>
{
public:
	typedef list_node_double<Item>* pnode;
	typedef list_node_double<Item>	node;
public:
	queue_list_double();
	virtual ~queue_list_double();
	virtual BOOL empty() const;
	virtual void put(Item item);
	virtual Item get();
protected:
	pnode	m_pHead;
	pnode	m_pTail;
};

template <typename Item>
queue_list_double<Item>::queue_list_double()
:m_pHead(DsNULL), m_pTail(DsNULL){
};

template <typename Item>
queue_list_double<Item>::~queue_list_double()
{
	queue_list_double<Item>::pnode pToBeDeleted = DsNULL;
	while(m_pTail)
	{
		pToBeDeleted = m_pTail;
		m_pTail = m_pTail->get_next();
		delete pToBeDeleted;
	}
};

template <typename Item>
BOOL queue_list_double<Item>::empty() const
{
	if(m_pTail != DsNULL)
		return FALSE;
	else
		return TRUE;
};

template <typename Item>
void queue_list_double<Item>::put(Item item)
{
	queue_list_double<Item>::pnode pNewNode = 
		new queue_list_double<Item>::node(item, DsNULL, m_pHead);
	if(pNewNode)
	{
		if(m_pHead)
			m_pHead->set_next(pNewNode);
		m_pHead = pNewNode;
		if(m_pTail == DsNULL)
			m_pTail = m_pHead;
	}
};

template <typename Item>
Item queue_list_double<Item>::get()
{
	Item iRet;
	if(!empty())
	{
		iRet = m_pTail->get_data();
		queue_list_double<Item>::pnode pNewTail = m_pTail->get_next();
		if(pNewTail)
		{
			pNewTail->set_prev(DsNULL);	
		}
		if(m_pTail == m_pHead)
			m_pHead = DsNULL;
		
		delete m_pTail;
		m_pTail = pNewTail;
	}
	else
	{
		cout<<"Error, queue_list::get, no element in queue."<<endl;
	}
	return iRet;
};

template <typename Item>
class queue_list_single: public iqueue<Item>
{
public:
	typedef list_node_single<Item>* pnode;
	typedef list_node_single<Item>	node;
public:
	queue_list_single();
	virtual ~queue_list_single();
	virtual BOOL empty() const;
	virtual void put(Item item);
	virtual Item get();
protected:
	pnode	m_pHead;
	pnode	m_pTail;
};

template <typename Item>
queue_list_single<Item>::queue_list_single()
:m_pHead(NULL), m_pTail(NULL){
};

template <typename Item>
queue_list_single<Item>::~queue_list_single()
{
	queue_list_single<Item>::pnode pToBeDeleted = NULL;
	while(m_pTail)
	{
		pToBeDeleted = m_pTail;
		m_pTail = m_pTail->get_next();
		delete pToBeDeleted;
	}
};

template <typename Item>
BOOL queue_list_single<Item>::empty() const
{
	if(m_pTail != NULL)
		return FALSE;
	else
		return TRUE;
};

template <typename Item>
void queue_list_single<Item>::put(Item item)
{
	queue_list_single<Item>::pnode pNewNode = 
		new queue_list_single<Item>::node(item, NULL);
	if(pNewNode)
	{
		if(m_pHead)
			m_pHead->set_next(pNewNode);
		m_pHead = pNewNode;
		if(m_pTail == NULL)
			m_pTail = m_pHead;
	}
};

template <typename Item>
Item queue_list_single<Item>::get()
{
	Item iRet = 0;
	if(!empty())
	{
		iRet = m_pTail->get_data();
		queue_list_single<Item>::pnode pNewTail = m_pTail->get_next();
		if(m_pTail == m_pHead)
			m_pHead = NULL;	
		delete m_pTail;
		m_pTail = pNewTail;
	}
//	else
//	{
//		cout<<"Error, queue_list::get, no element in queue."<<endl;
//	}
	return iRet;
};
#endif //_INCLUDED_QUEUE_HPP_