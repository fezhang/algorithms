#ifndef _INCLUDED_POLYNOMIAL_HPP_
#define _INCLUDED_POLYNOMIAL_HPP_

#include "list.hpp"

struct nomial
{
	nomial(int nIndex, int nTimes):_nTimes(nTimes), _nIndex(nIndex){};
	int _nIndex;
	int	_nTimes;
};

//item = int or float or others
//in this list index is from big to little
template <typename Item>
class polynomial
{
public:
	typedef list_node_double<nomial>	t_node;
	typedef list_node_double<nomial>*	t_pnode;

public:
	polynomial();									//DONE
	virtual ~polynomial();							//DONE
	polynomial(polynomial<Item>&);					//DONE
	polynomial<Item>& operator=(polynomial<Item>&);	//DONE

public:
	polynomial<Item>& operator+(polynomial<Item>&);	//DONE
	polynomial<Item>& operator-(polynomial<Item>&);	//DONE
	polynomial<Item> operator*(polynomial<Item>&);	//DONE

	BOOL operator==(polynomial<Item>&);				//DONE
	BOOL operator!=(polynomial<Item>&);				//DONE

public:
	Item evaluate(Item) const;				//DONE
	void add_item(int nIndex, int nTimes);	//DONE
	void output();							//DONE

protected:
	int change_item_index(t_pnode, int nIndex);	//DONE
	void clear_all_items();						//DONE
	void clear_zero_items();					//DONE
	t_pnode	m_head;								//DONE
};

template <typename Item>
polynomial<Item>::polynomial()
:m_head(DsNULL)
{
	OUT_CD(cout<<"Constructor: polynomial<Item>::polynomial"<<endl);
};

template <typename Item>
polynomial<Item>::~polynomial()
{
	OUT_CD(cout<<"Destructor: polynomial<Item>::~polynomial"<<endl);
	clear_all_items();
};

template <typename Item>
polynomial<Item>::polynomial(polynomial<Item>& rhs)
:m_head(DsNULL)
{
	OUT_CD(cout<<"Constructor: polynomial<Item>::polynomial(polynomial<Item>&)"<<endl);
	list_node_double<nomial>* pRhsNode = rhs.m_head;
	list_node_double<nomial>* pMyNode = DsNULL;
	while(pRhsNode)
	{
		list_node_double<nomial>* pNewNode =
			new list_node_double<nomial>(pRhsNode->get_data(), DsNULL, pMyNode);
		if(pMyNode)
			pMyNode->set_next(pNewNode);
		pMyNode = pNewNode;

		if(m_head == DsNULL)
			m_head = pNewNode;

		pRhsNode = pRhsNode->get_next();
	}
};

template <typename Item>
polynomial<Item>& polynomial<Item>::operator=(polynomial& rhs)
{
	OUT_CD(cout<<"Assignment: polynomial<Item>::operator="<<endl);
	if(&rhs == this)
		return *this;

	clear_all_items();

	list_node_double<nomial>* pRhsNode = rhs.m_head;
	list_node_double<nomial>* pMyNode = DsNULL;
	while(pRhsNode)
	{
		list_node_double<nomial>* pNewNode =
			new list_node_double<nomial>(pRhsNode->get_data(), DsNULL, pMyNode);
		if(pMyNode)
			pMyNode->set_next(pNewNode);
		pMyNode = pNewNode;

		if(m_head == DsNULL)
			m_head = pNewNode;

		pRhsNode = pRhsNode->get_next();
	}

	return *this;
};

template <typename Item>
polynomial<Item>& polynomial<Item>::operator+(polynomial& rhs)
{
	list_node_double<nomial>* pRhsNode = rhs.m_head;
	list_node_double<nomial>* pMyNode = m_head;
	list_node_double<nomial>* pMyNodePrev = DsNULL;
	
	if(&rhs == this) // add myself
	{
		while(pMyNode)
		{
			pMyNode->get_data()._nIndex *= 2;
			pMyNode = pMyNode->get_next();
		}
		return *this;
	}

	while(pRhsNode)
	{
		if(pMyNode == DsNULL || pRhsNode->get_data()._nTimes > pMyNode->get_data()._nTimes)
		{ // add this node directly
			list_node_double<nomial>* pNewNode = 
				new list_node_double<nomial>(
					nomial(pRhsNode->get_data()._nIndex,pRhsNode->get_data()._nTimes), 
					pMyNode, pMyNode?pMyNode->get_prev():DsNULL);

			if(pMyNode)
				pMyNode->set_prev(pNewNode);
			if(pMyNodePrev)
			{
				pMyNodePrev->set_next(pNewNode);
				pMyNodePrev = pNewNode;
			}

			if(pMyNode == m_head || m_head == DsNULL)
				m_head = pNewNode;

			pRhsNode = pRhsNode->get_next();
		}
		else if(pRhsNode->get_data()._nTimes < pMyNode->get_data()._nTimes)
		{ // left side search, and add to left side
			pMyNodePrev = pMyNode;
			pMyNode = pMyNode->get_next();
		}
		else// if(pRhsNode.get_data()._nTimes == pThisNode.get_data()._nTimes)
		{ // add the index directly

			if(0 == change_item_index(
				pMyNode, 
				pMyNode->get_data()._nIndex+pRhsNode->get_data()._nIndex))
			{//remove this item
				if(pMyNode->get_prev())
					pMyNode->get_prev()->set_next(pMyNode->get_next());
				if(pMyNode->get_next())
					pMyNode->get_next()->set_prev(pMyNode->get_prev());

				list_node_double<nomial>* pToBeDeleted = pMyNode;
				
				if(pMyNode == m_head)
				{
					m_head = pMyNode->get_next();
				}
				pMyNodePrev = pMyNode->get_prev();
				pMyNode = pMyNode->get_next();

				delete pToBeDeleted;	
			}
			else{
				pMyNodePrev = pMyNode;
				pMyNode = pMyNode->get_next();
			}
			pRhsNode = pRhsNode->get_next();
		}
	}
	return *this;
};

template <typename Item>
polynomial<Item>& polynomial<Item>::operator-(polynomial& rhs)
{
	list_node_double<nomial>* pRhsNode = rhs.m_head;
	list_node_double<nomial>* pMyNode = m_head;
	list_node_double<nomial>* pMyNodePrev = DsNULL;
	
	if(&rhs == this)
	{
		clear_all_items();
		return *this;
	}

	while(pRhsNode)
	{
		if(pMyNode == DsNULL || pRhsNode->get_data()._nTimes > pMyNode->get_data()._nTimes)
		{ // add this node directly
			list_node_double<nomial>* pNewNode = 
				new list_node_double<nomial>(
					nomial(-1*pRhsNode->get_data()._nIndex,pRhsNode->get_data()._nTimes), 
					pMyNode, pMyNode?pMyNode->get_prev():DsNULL);

			if(pMyNode)
				pMyNode->set_prev(pNewNode);
			if(pMyNodePrev)
			{
				pMyNodePrev->set_next(pNewNode);
				pMyNodePrev = pNewNode;
			}

			if(pMyNode == m_head || m_head == DsNULL)
				m_head = pNewNode;

			pRhsNode = pRhsNode->get_next();
		}
		else if(pRhsNode->get_data()._nTimes < pMyNode->get_data()._nTimes)
		{ // left side search, and add to left side
			pMyNodePrev = pMyNode;
			pMyNode = pMyNode->get_next();
		}
		else// if(pRhsNode.get_data()._nTimes == pThisNode.get_data()._nTimes)
		{ // add the index directly

			if(0 == change_item_index(
				pMyNode, 
				pMyNode->get_data()._nIndex-pRhsNode->get_data()._nIndex))
			{//remove this item
				if(pMyNodePrev)
					pMyNodePrev->set_next(pMyNode->get_next());
				if(pMyNode->get_next())
					pMyNode->get_next()->set_prev(pMyNode->get_prev());

				list_node_double<nomial>* pToBeDeleted = pMyNode;
				
				if(pMyNode == m_head)
				{
					m_head = pMyNode->get_next();
				}
				pMyNodePrev = pMyNode->get_prev();
				pMyNode = pMyNode->get_next();

				delete pToBeDeleted;	
			}
			else{
				pMyNodePrev = pMyNode;
				pMyNode = pMyNode->get_next();
			}
			pRhsNode = pRhsNode->get_next();
		}
	}
	return *this;
};

template <typename Item>
polynomial<Item> polynomial<Item>::operator*(polynomial& rhs)
{
	clear_zero_items();
	rhs.clear_zero_items();

	polynomial<Item> pnRet;
	list_node_double<nomial>* pMyNode = m_head;
	list_node_double<nomial>* pRhsNode = rhs.m_head;
	int nRhsIndex = 0, nRhsTime = 0;
	int nNewIndex = 0, nNewTime = 0; 

	while(pRhsNode)
	{
		nRhsIndex = pRhsNode->get_data()._nIndex;
		nRhsTime = pRhsNode->get_data()._nTimes;
		pMyNode = m_head;
		
		while(pMyNode)
		{
			nNewIndex = pMyNode->get_data()._nIndex * nRhsIndex;
			nNewTime = pMyNode->get_data()._nTimes + nRhsTime;
			pnRet.add_item(nNewIndex, nNewTime);
			pMyNode = pMyNode->get_next();
		}

		pRhsNode = pRhsNode->get_next();
	}
	return pnRet;
};

template <typename Item>
BOOL polynomial<Item>::operator==(polynomial<Item>& rhs)
{
	clear_zero_items();
	rhs.clear_zero_items();
	list_node_double<nomial>* pMyNode = m_head;
	list_node_double<nomial>* pRhsNode = rhs.m_head;
	while(pMyNode && pRhsNode)
	{
		if( pMyNode->get_data()._nIndex != pRhsNode->get_data()._nIndex
		 || pMyNode->get_data()._nTimes != pRhsNode->get_data()._nTimes)
		 return FALSE;
		pMyNode = pMyNode->get_next();
		pRhsNode = pRhsNode->get_next();
	}
	if(pMyNode || pRhsNode)
		return FALSE;

	return TRUE;
};

template <typename Item>
BOOL polynomial<Item>::operator!=(polynomial<Item>& rhs)
{
	return *this==rhs?FALSE:TRUE;	//use operator ==
};

template <typename Item>
Item polynomial<Item>::evaluate(Item seed) const
{
	Item itemRet = 0;
	Item itemRetDotPart = 0;

	int nStep = 0, i = 0;
	int nLastTimes = 0;
	
	list_node_double<nomial>* pTemp = m_head;
	while(pTemp && pTemp->get_data()._nTimes>0)
	{
		nStep = 0;
		if(pTemp->get_prev())
			nStep =	nLastTimes - pTemp->get_data()._nTimes;

		for(i=0; i<nStep; ++i)
			itemRet *= seed;

		itemRet += pTemp->get_data()._nIndex*seed;

		nLastTimes = pTemp->get_data()._nTimes;
		pTemp = pTemp->get_next();
	}
	nStep = nLastTimes-1;
	if(nStep >=1)
	{
		for(i=0; i<nStep; ++i)
			itemRet *= seed;
	}
	if(pTemp)
	{
		if(pTemp->get_data()._nTimes == 0)
		{
			itemRet += pTemp->get_data()._nIndex;
			pTemp = pTemp->get_next();
		}
	}
	//calculate nTimes<0 part
	while(pTemp)
	{
		nStep = 0;
		if(nLastTimes>=0)
		{
			nStep = -pTemp->get_data()._nTimes;
		}
		else
		{
			nStep = nLastTimes-pTemp->get_data()._nTimes;
		}
		
		for(i=0; i<nStep; ++i)
			itemRetDotPart *= seed;

		itemRetDotPart += pTemp->get_data()._nIndex*seed;

		nLastTimes = pTemp->get_data()._nTimes;
		pTemp = pTemp->get_next();
	}

	if(itemRetDotPart != 0)
		itemRet += 1/itemRetDotPart;
	return itemRet;
};

template <typename Item>
void polynomial<Item>::add_item(int nIndex, int nTimes)
{
	OUT_FU(cout<<"		polynomial<Item>::add_item, add ("<<nIndex<<","<<nTimes<<")"<<endl);
	if(0 == nIndex)
		return;

	list_node_double<nomial>* pTemp = m_head;
	list_node_double<nomial>* pTail = DsNULL;
	BOOL bInsearted = FALSE;
	while(pTemp)
	{
		pTail = pTemp;
		if(pTemp->get_data()._nTimes<nTimes)
		{  // add an item here
			list_node_double<nomial>* pNewNode = 
				new list_node_double<nomial>(nomial(nIndex, nTimes), pTemp, pTemp->get_prev());
			if(pTemp->get_prev())
				pTemp->get_prev()->set_next(pNewNode);
			pTemp->set_prev(pNewNode);
			if(pTemp == m_head)
				m_head = pNewNode;

			bInsearted = TRUE;
			break;
		}
		else if(pTemp->get_data()._nTimes == nTimes)
		{ // add index directly, if find index==0, we should remove this node
			if( 0 == change_item_index(pTemp, pTemp->get_data()._nIndex+nIndex) )
			{
				if(pTemp->get_prev())
					pTemp->get_prev()->set_next(pTemp->get_next());
				if(pTemp->get_next())
					pTemp->get_next()->set_prev(pTemp->get_prev());

				if(pTemp == m_head)
				{
					m_head = pTemp->get_next();
				}
				delete pTemp;
			};
			
			bInsearted = TRUE;
			break;
		}
		pTemp = pTemp->get_next();
	}

	if(!bInsearted)
	{ // insert at last position
		list_node_double<nomial>* pLastNode = 
				new list_node_double<nomial>(nomial(nIndex, nTimes), DsNULL, pTail);
		if(pTail)
			pTail->set_next(pLastNode);
		else if(pTail == DsNULL)	//there is no nodes in list
			m_head = pLastNode;

	}
	return;
};

template <typename Item>
int polynomial<Item>::change_item_index(list_node_double<nomial>* pNode, int nIndex)
{
	if(pNode)
	{
		pNode->get_data()._nIndex = nIndex;
		return nIndex;
	}
	return 0;
};

template <typename Item>	
void polynomial<Item>::clear_all_items()
{
	list_node_double<nomial>* pToBeDeleted = m_head;
	while(m_head)
	{
		pToBeDeleted = m_head;
		m_head = m_head->get_next();
		delete pToBeDeleted;
	}
	m_head = DsNULL;
	return;
};

template <typename Item>	
void polynomial<Item>::output()
{
	list_node_double<nomial>* pTemp = m_head;
	while(pTemp)
	{
		if(pTemp != m_head)
			cout<<" + ";

		cout<<pTemp->get_data()._nIndex<<"*";
		cout<<"POW(X,"<<pTemp->get_data()._nTimes<<")";

		pTemp = pTemp->get_next();
	}
	cout<<endl;

	return;
};

template <typename Item>
void polynomial<Item>::clear_zero_items()
{
	list_node_double<nomial>* pTemp = m_head;
	list_node_double<nomial>* pToBeDeleted = DsNULL;
	while(pTemp)
	{
		if(pTemp->get_data()._nIndex == 0)
		{
			pToBeDeleted = pTemp;
			if(m_head == pTemp)
				m_head = pTemp->get_next();
			if(pTemp->get_prev())
				pTemp->get_prev()->set_next(pTemp->get_next());
			if(pTemp->get_next())
				pTemp->get_next()->set_prev(pTemp->get_prev());
			pTemp = pTemp->get_next();
			delete pToBeDeleted;
		}
		else
		{
			pTemp = pTemp->get_next();
		}
	}
};
#endif //_INCLUDED_POLYNOMIAL_HPP_