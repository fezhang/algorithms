#ifndef _INCLUDED_BASIC_SORTING_HPP_
#define _INCLUDED_BASIC_SORTING_HPP_

#include "platform.h"
#include "list.hpp"
#include "vector.hpp"

template <typename Item>
void comex(Item& l, Item& r)
{
	if(l>r)
	{
		Item temp = l;
		l = r;
		r = temp;
	}
}

template <typename Item>
BOOL compexch(Item& l, Item& r)
{
	if(l>r)
	{
		Item temp = l;
		l = r;
		r = temp;
		return TRUE;
	}
	return FALSE;
}

template <typename Item>
class vector_sort
{
public:
	static void bubble(_vector<Item>*);
	static void bubble2(_vector<Item>*);
	static void selection(_vector<Item>*);
	static void insertion(_vector<Item>*);
	static void insertion2(_vector<Item>*);
	static void shell(_vector<Item>*);
};

template <typename Item>
/*static*/ void vector_sort<Item>::bubble(_vector<Item>* pVector)
{
	if(!pVector || pVector->size() == 0)
		return;
	
	for(int i=pVector->size()-1; i>=1; --i)
	{
		for(int j=0; j<i; ++j)
		{
			comex((*pVector)[j],(*pVector)[j+1]);
		}
	}
};

template <typename Item>
/*static*/ void vector_sort<Item>::bubble2(_vector<Item>* pVector)
{
	if(!pVector || pVector->size() == 0)
		return;
	
	BOOL bDoExchange = FALSE;
	for(int i=pVector->size()-1; i>=1; --i)
	{
		bDoExchange = FALSE;
		for(int j=0; j<i; ++j)
		{
			BOOL bExchange = compexch((*pVector)[j],(*pVector)[j+1]);
			if(!bDoExchange)
				bDoExchange = bExchange;
		}
		if(!bDoExchange)
			break;
	}
};

template <typename Item>
/*static*/ void vector_sort<Item>::selection(_vector<Item>* pVector)
{
	if(!pVector || 0 == pVector->size())
		return;

	Item itMax = (*pVector)[0];
	int nIdxMax = 0;

	for(int i=pVector->size()-1; i>=1; --i)
	{
		nIdxMax = 0;
		for(int j=1; j<=i; ++j)
		{
			if((*pVector)[j] > (*pVector)[nIdxMax])
				nIdxMax = j;
		}
		Exchange((*pVector)[nIdxMax], (*pVector)[i]);
	}
};

template <typename Item>
/*static*/ void vector_sort<Item>::insertion(_vector<Item>* pVector)
{
	if(!pVector || 0 == pVector->size())
		return;

	Item itTemp = (*pVector)[0];
	int nPos = 0;

	for(int i=0; i<pVector->size()-1; ++i)
	{
		if((*pVector)[i+1] >= (*pVector)[i])
			continue;

		itTemp = (*pVector)[i+1];
		for(nPos=i; nPos>=0; --nPos)
		{
			if((*pVector)[nPos]>itTemp)
				(*pVector)[nPos+1] =  (*pVector)[nPos];
			else
				break;
		}
		(*pVector)[nPos+1] = itTemp;
	}
};

template <typename Item>
/*static*/ void vector_sort<Item>::insertion2(_vector<Item>* pVector)
{
	if(!pVector || 0 == pVector->size())
		return;

	Item itTemp = (*pVector)[0];
	int nPos = 0;
	int i=0;

	for(i=1; i<pVector->size();++i)
		if((*pVector)[i] < (*pVector)[nPos])
			nPos = i;

	if(nPos!=0)
		Exchange((*pVector)[0], (*pVector)[nPos]);

	for(i=2; i<pVector->size(); ++i)
	{
		if((*pVector)[i] >= (*pVector)[i-1])
			continue;

		itTemp = (*pVector)[i];
		nPos = i-1;
		while((*pVector)[nPos]>itTemp)
		{
			(*pVector)[nPos+1] =  (*pVector)[nPos];
			--nPos;
		}
		
		(*pVector)[nPos+1] = itTemp;
	}
};

template <typename Item>
/*static*/ void vector_sort<Item>::shell(_vector<Item>* pVector)
{
	if(!pVector || 0 == pVector->size())
		return;

	//shell rearrange
	int nStep = 1;
	for(nStep=1; nStep<(pVector->size())/9;nStep=nStep*3+1);
	Item itTemp;
	int nPos;

	for(nStep; nStep>=1; nStep=(nStep-1)/3)
	{
		//insertion rearrange
		for(int i=nStep;i<pVector->size(); i+=nStep)
		{
			if((*pVector)[i] > (*pVector)[i-nStep])
				continue;
			itTemp = (*pVector)[i];
			nPos = i-nStep;
			while((*pVector)[nPos] > itTemp && nPos>0)
			{
				(*pVector)[nPos+nStep] = (*pVector)[nPos];
				nPos -= nStep;
			}
			(*pVector)[nPos+nStep] = itTemp;
		}
	}
};

template <typename Item>
class sing_list_sort
{
public:
	static void bubble(list_single<Item>*);
	static void selection(list_single<Item>*);
	static void insertion(list_single<Item>*);
	static void shell(list_single<Item>*);
};

template <typename Item>
/*static*/ void sing_list_sort<Item>::bubble(list_single<Item>* pList)
{
	if(!pList || 1 >= pList->size())
		return;

	list_node_single<Item>* pPos = NULL;
	list_node_single<Item>* pPosNext = NULL;
	list_node_single<Item>* pPosGood = NULL;

	while(pPosGood != pList->get_head()->get_next()
		&& pPosGood != pList->get_head())
	{
		pPos = pList->get_head();
		pPosNext = pPos->get_next();

		if(pPosNext->get_data() < pPos->get_data())
		{ //exchange head and head next
			pList->set_head(pPosNext);
			pPos->set_next(pPosNext->get_next());
			pPosNext->set_next(pPos);
			
			pPos = pList->get_head();
			pPosNext = pPos->get_next();
		}

		while(pPosNext->get_next() != pPosGood)
		{
			if(pPosNext->get_data() > pPosNext->get_next()->get_data())
			{ //exchange two node
				pPos->set_next(pPosNext->get_next());
				list_node_single<Item>* pPosNNN = pPosNext->get_next()->get_next();
				pPosNext->get_next()->set_next(pPosNext);
				pPosNext->set_next(pPosNNN);
			}
			pPos = pPos->get_next();
			pPosNext = pPos->get_next();
		}
		pPosGood = pPosNext;
	}
};

template <typename Item>
/*static*/ void sing_list_sort<Item>::selection(list_single<Item>* pList)
{
	if(!pList || 1 >= pList->size())
		return;

	list_node_single<Item>* pLastOK = NULL;
	list_node_single<Item>* pPreMin = NULL;
	list_node_single<Item>* pPos = NULL;

	while( pLastOK== NULL || pLastOK->get_next() != NULL)
	{
		pPreMin = pLastOK;
		pPos = pLastOK?pLastOK->get_next():pList->get_head();

		//find smallest one
		while(pPos->get_next())
		{
			if(pPos->get_next()->get_data() < 
				(pPreMin?(pPreMin->get_next()->get_data()):pList->get_head()->get_data())
				)
			{
				pPreMin = pPos;
			}
			pPos = pPos->get_next();
		}
		//remove first, and then insert
		list_node_single<Item>* pMin = pPreMin?pPreMin->get_next():pList->get_head();
		if(pPreMin)
			pPreMin->set_next(pPreMin->get_next()->get_next());
		else
			pList->set_head(pList->get_head()->get_next());

		if(pLastOK)
		{
			pMin->set_next(pLastOK->get_next());
			pLastOK->set_next(pMin);
		}
		else	//last ok is head
		{
			pMin->set_next(pList->get_head());
			pList->set_head(pMin);
		}

		pLastOK = pMin;
	}
};

template <typename Item>
/*static*/ void sing_list_sort<Item>::insertion(list_single<Item>* pList)
{
	if(!pList || 1 >= pList->size())
		return;

	cout<<"no implementation!"<<endl;
};

template <typename Item>
/*static*/ void sing_list_sort<Item>::shell(list_single<Item>* pList)
{
	cout<<"no implementation!"<<endl;
};

#endif //_INCLUDED_BASIC_SORTING_HPP_