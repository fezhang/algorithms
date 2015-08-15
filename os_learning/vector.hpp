#ifndef _INCLUDED_VECTOR_HPP_
#define _INCLUDED_VECTOR_HPP_

#include "container.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DsNULL NULL

//use _vector to diff with std::vector

template <typename Item>
class _vector: public icontainer<Item>
{
public:
	enum{ _SIZE_MINIMIZED_ = 16};
	_vector();
	_vector(int nSize);
	_vector(Item*, int nLen);
	virtual ~_vector();

public:
	virtual void push_front(Item){};			//no implementation
	virtual Item pop_front(){return Item();};	//no implementation
	virtual Item pop_back(){return Item();};	//no implementation

	virtual void push_back(Item);	
	virtual int size();
	virtual Item& operator[](int nIndex);

	BOOL remove(Item);
    BOOL remove(int idx);
	int find(Item);
	_vector<Item>* clone();

	Item* GetBase();
protected:
	BOOL expand();
	void init(int size);
	Item*	m_pBase;
	int		m_nAllocated;
	int		m_nUsed;

protected:
	_vector(_vector<Item>&);				//no implementation
	_vector<Item>& operator=(_vector<Item>&);	//no implementation
	BOOL operator>(_vector<Item>&);		//no implementation
	//...
};

//////////////////////////////////////////////////////////////////////////
// implementation
template <typename Item>
_vector<Item>::_vector()
:m_pBase(DsNULL), m_nAllocated(0),m_nUsed(0)
{
	init(_vector::_SIZE_MINIMIZED_);
};

template <typename Item>
_vector<Item>::_vector(int nSize)
:m_pBase(DsNULL), m_nAllocated(0),m_nUsed(0)
{
	if(nSize < _vector::_SIZE_MINIMIZED_)
		nSize = _vector::_SIZE_MINIMIZED_;

	init(nSize);
};

template <typename Item>
_vector<Item>::_vector(Item* data, int nLen)
:m_pBase(DsNULL), m_nAllocated(0),m_nUsed(0)
{
	if(!data || nLen<=0)
	{
		init(_vector::_SIZE_MINIMIZED_);
	}
	else
	{	//should copy data here
		if(nLen < _vector::_SIZE_MINIMIZED_)
			init(_vector::_SIZE_MINIMIZED_);
		else
			init((nLen/_vector::_SIZE_MINIMIZED_+1)*(_vector::_SIZE_MINIMIZED_));

		if(m_pBase)
		{
			memcpy(m_pBase, data, nLen*sizeof(Item));
			m_nUsed = nLen;
		}
	}
};

template <typename Item>
_vector<Item>::~_vector()
{
	if(m_pBase)
		delete[] m_pBase;
};

template <typename Item>
void _vector<Item>::push_back(Item data)
{
	if(m_nUsed == m_nAllocated && !expand())
		return;

	m_pBase[m_nUsed++] = data;
};
	
template <typename Item>
int _vector<Item>::size()
{
	return m_nUsed;
};

template <typename Item>
Item& _vector<Item>::operator[](int nIndex)
{
	return m_pBase[nIndex];	//don't check index
};

template <typename Item>
BOOL _vector<Item>::remove(Item data)
{
	int nIndex = find(data);
	if(nIndex == -1)
		return FALSE;
	else
	{
		memcpy(m_pBase+nIndex, m_pBase+nIndex+1; m_nUsed-nIndex-1);
		--m_nUsed;
		return TRUE;
	}
};

template <typename Item>
BOOL _vector<Item>::remove(int idx)
{
    if(idx<0 || idx>=size())
        return false;
    else
    {
        memcpy(m_pBase+idx, m_pBase+idx+1, m_nUsed-idx-1);
		--m_nUsed;
		return true;
    }
};

template <typename Item>
int _vector<Item>::find(Item data)
{ //search, low efficiency
	int nIndex = -1;
	for(int i=0; i<m_nUsed; ++i)
	{
		if(m_pBase[i] == data)
		{
			nIndex = i;
			break;
		}
	}
	return nIndex;
};

template <typename Item>
Item* _vector<Item>::GetBase()
{
	return m_pBase;
};

template <typename Item>
_vector<Item>* _vector<Item>::clone()
{
	cout<<"_vector::clone method hasn't implemented now!"<<endl;
	return DsNULL;
};

template <typename Item>
void _vector<Item>::init(int size)
{
	m_pBase = new Item[size];
	if(m_pBase)
	{
		memset(m_pBase, 0, size*sizeof(Item));
		m_nAllocated = size;
	}
};

template <typename Item>
BOOL _vector<Item>::expand()
{
	if(!m_pBase)
	{
		init(_vector::_SIZE_MINIMIZED_);
		return TRUE;
	}
	Item* pNewBase = new Item[m_nAllocated*2];
	if(!pNewBase)
		return FALSE;

	memcpy(pNewBase, m_pBase, m_nUsed*sizeof(Item));
	m_nAllocated *= 2;
	delete[] m_pBase;
	m_pBase = pNewBase;
	
	return TRUE;
};
// end of implementation of class _vector
//////////////////////////////////////////////////////////////////////////

#endif //_INCLUDED_VECTOR_HPP_