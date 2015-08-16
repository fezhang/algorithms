#ifndef _INCLUDED_ELEMENTARY_SORT_FRAMEWORK_H_
#define _INCLUDED_ELEMENTARY_SORT_FRAMEWORK_H_

#include "basic_sort.hpp"

class basic_sort
{
public:
	static void test_basic_sort();
	static void test_vector_sort();
	static void test_list_sort();
	static void run_one_vector_sort(void (pf)(_vector<int>*), int nLen, DsBOOL bOutput=DsFALSE, DsBOOL bSortAgain=DsFALSE, DsBOOL bNeedVerify=DsFALSE);
	static void run_one_list_sort(void (pf)(list_single<int>*), int nLen, 
		DsBOOL bOutput, DsBOOL bSortAgain, DsBOOL bNeedVerify,void (pf2)(list_single<int>*));

	virtual ~basic_sort()
	{
		if(m_pVector)
			delete m_pVector;
		if(m_pSlist)
			delete m_pSlist;
	}
protected:
	basic_sort(){ m_pVector = DsNULL, m_pSlist = DsNULL;};
	DsBOOL generate_rand_vector(int nLen);
	void free_vector();
	void output_vector();

	DsBOOL generate_rand_list(int nLen);
	void free_list();
	void output_list();

	_vector<int>*			m_pVector;
	list_single<int>*		m_pSlist;
};
#endif //_INCLUDED_ELEMENTARY_SORT_FRAMEWORK_H_