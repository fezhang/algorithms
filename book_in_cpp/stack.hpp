#ifndef _INCLUDED_STACK_HPP_
#define _INCLUDED_STACK_HPP_

#include "list.hpp"

//stack interface
template <typename Item>
class stack
{
public:
	stack(int);
	virtual ~stack();
	int empty() const;
	void push(Item item);
	Item pop();
	Item top() const;
protected:
	Item*	m_pBase;
	int		m_nTop;
	int		m_nBuffLen;
};

template <typename Item>
stack<Item>::stack(int nLen)
:m_pBase(DsNULL), m_nTop(-1), m_nBuffLen(0)
{
	m_pBase = new Item[nLen];
	if(m_pBase)
	{
		m_nBuffLen = nLen;
	}
}

template <typename Item>
stack<Item>::~stack()
{
	if(m_pBase)
		delete[] m_pBase;
}

template <typename Item>
int stack<Item>::empty() const
{
	if(-1==m_nTop)
		return DsTRUE;
	else
		return DsFALSE;
}

template <typename Item>
void stack<Item>::push(Item item)
{
	if(m_nTop+1 >= m_nBuffLen) //alloc memory
	{
		Item* pNewBase = new Item[m_nBuffLen*2];
		if(pNewBase)
		{
			if(m_pBase && m_nTop!=-1)
			{
				memcpy(pNewBase, m_pBase, m_nBuffLen);
				delete[] m_pBase;
				m_pBase = pNewBase;
				m_nBuffLen = m_nBuffLen*2;
			}
		}
	}
	
	if(m_pBase)
	{
		m_pBase[m_nTop+1] = item;
		++m_nTop;
	}
}

template <typename Item>
Item stack<Item>::pop()
{
	if(empty())
		return Item();
	else
		return m_pBase[m_nTop--];
}

template <typename Item>
Item stack<Item>::top() const
{
	if(empty())
		return Item();
	else
		return m_pBase[m_nTop];
};

// implemented by list
template <typename Item>
class stack_l
{
protected:
	typedef list_node_single<Item>* p_node;
	typedef list_node_single<Item>  node;

public:
	stack_l(int = 0);	//this parameter is useless
	virtual ~stack_l();
	int empty() const;
	void push(Item item);
	Item pop();
	Item top() const;
protected:
	p_node	m_pHead;
};

template <typename Item>
stack_l<Item>::stack_l(int n)
:m_pHead(DsNULL){
}

template <typename Item>
stack_l<Item>::~stack_l()
{
	stack_l<Item>::p_node pTemp = m_pHead;
	stack_l<Item>::p_node pToBeDeleted = DsNULL;
	while(pTemp != DsNULL)
	{
		pToBeDeleted = pTemp;
		pTemp = pTemp->get_next();
		delete pToBeDeleted;
	}
}

template <typename Item>
int stack_l<Item>::empty() const
{
	return (m_pHead == DsNULL);
};

template <typename Item>
void stack_l<Item>::push(Item item)
{//insert a node after m_pHead
	stack_l<Item>::p_node pNewNode = new stack_l<Item>::node(item);
	if(pNewNode)
	{
		pNewNode->set_next(m_pHead);
		m_pHead = pNewNode;
	}
};

template <typename Item>
Item stack_l<Item>::pop()
{
	Item iRet;
	if(m_pHead)
	{
		iRet = m_pHead->get_data();
		stack_l<Item>::p_node pToBeDeleted = m_pHead;
		m_pHead = m_pHead->get_next();
		delete pToBeDeleted;
	}

	return iRet;
};

template <typename Item>
Item stack_l<Item>::top() const
{
	Item iRet;
	if(m_pHead)
	{
		iRet = m_pHead->get_data();
	}

	return iRet;
};
#endif //_INCLUDED_STACK_HPP_