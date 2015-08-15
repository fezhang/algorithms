#include "elementary_sort_frame.h"

/*static*/ void basic_sort::test_basic_sort()
{
	cout<<"**** test vector sort:"<<endl;
	test_vector_sort();
	cout<<"**** test list sort:"<<endl;
	test_list_sort();
};

/*static*/ void basic_sort::test_vector_sort()
{
	cout<<"bubble sort: "<<endl;
//	run_one_vector_sort(vector_sort<int>::bubble, 100);
//	run_one_vector_sort(vector_sort<int>::bubble, 200);
//	run_one_vector_sort(vector_sort<int>::bubble, 400);
//	run_one_vector_sort(vector_sort<int>::bubble, 800);
//	run_one_vector_sort(vector_sort<int>::bubble, 1600);
//	run_one_vector_sort(vector_sort<int>::bubble, 3200);
//   	run_one_vector_sort(vector_sort<int>::bubble, 6400);

	cout<<"bubble2 sort: "<<endl;
//	run_one_vector_sort(vector_sort<int>::bubble2, 100);
//	run_one_vector_sort(vector_sort<int>::bubble2, 200);
//	run_one_vector_sort(vector_sort<int>::bubble2, 400);
//	run_one_vector_sort(vector_sort<int>::bubble2, 800);
//	run_one_vector_sort(vector_sort<int>::bubble2, 1600);
//	run_one_vector_sort(vector_sort<int>::bubble2, 3200);
 // 	run_one_vector_sort(vector_sort<int>::bubble2, 6400);
//
	cout<<"selection sort: "<<endl;
//	run_one_vector_sort(vector_sort<int>::selection, 100);
//	run_one_vector_sort(vector_sort<int>::selection, 200);
//	run_one_vector_sort(vector_sort<int>::selection, 400);
//	run_one_vector_sort(vector_sort<int>::selection, 800);
//	run_one_vector_sort(vector_sort<int>::selection, 1600);
//	run_one_vector_sort(vector_sort<int>::selection, 3200);
//	run_one_vector_sort(vector_sort<int>::selection, 6400);
//
	cout<<"insertion sort: "<<endl;
//	run_one_vector_sort(vector_sort<int>::insertion, 100);
//	run_one_vector_sort(vector_sort<int>::insertion, 200);
//	run_one_vector_sort(vector_sort<int>::insertion, 400);
//	run_one_vector_sort(vector_sort<int>::insertion, 800);
//	run_one_vector_sort(vector_sort<int>::insertion, 1600);
//	run_one_vector_sort(vector_sort<int>::insertion, 3200);
//	run_one_vector_sort(vector_sort<int>::insertion, 6400);
//
	cout<<"insertion2 sort: "<<endl;
//	run_one_vector_sort(vector_sort<int>::insertion2, 100);
//	run_one_vector_sort(vector_sort<int>::insertion2, 200);
//	run_one_vector_sort(vector_sort<int>::insertion2, 400);
//	run_one_vector_sort(vector_sort<int>::insertion2, 800);
//	run_one_vector_sort(vector_sort<int>::insertion2, 1600);
//	run_one_vector_sort(vector_sort<int>::insertion2, 3200);
//  run_one_vector_sort(vector_sort<int>::insertion2, 6400);

	cout<<"shell sort: "<<endl;
//	run_one_vector_sort(vector_sort<int>::shell, 100);
//	run_one_vector_sort(vector_sort<int>::shell, 200);
//	run_one_vector_sort(vector_sort<int>::shell, 400);
//	run_one_vector_sort(vector_sort<int>::shell, 800);
//	run_one_vector_sort(vector_sort<int>::shell, 1600);
//	run_one_vector_sort(vector_sort<int>::shell, 3200);
// 	run_one_vector_sort(vector_sort<int>::shell, 6400);
};

/*static*/ void basic_sort::run_one_vector_sort(void (pf)(_vector<int>*), int nLen, 
		BOOL bOutput, BOOL bSortAgain, BOOL bNeedVerify)
{
	timer ter;
	basic_sort bs;
	bs.generate_rand_vector(nLen);
	if(bOutput)
	{	
		cout<<"before sort:"<<endl;
		bs.output_vector();
	}
//
	ter.Reset();
	pf(bs.m_pVector);
	cout<<"sort timer during nLen = "<<nLen<<" is "<<(unsigned int)ter.Interval()<<endl;
//

	if(bSortAgain)
	{
		// sort again, check timer
		ter.Reset();
		pf(bs.m_pVector);
		cout<<"	sort timer during nLen = "<<nLen<<" is "<<(unsigned int)ter.Interval()<<endl;
	}

	if(bOutput)
	{
		cout<<"after sort:"<<endl;
		bs.output_vector();
	}

	if(bNeedVerify)
	{
		// using simplest sort "bubble sort" test again
		vector_sort<int>::bubble(bs.m_pVector);
		cout<<"after bubble sort:"<<endl;
		bs.output_vector();
	}

	bs.free_vector();
};

/*static*/ void basic_sort::run_one_list_sort(void (pf)(list_single<int>*), int nLen, 
		BOOL bOutput, BOOL bSortAgain, BOOL bNeedVerify, void (pf2)(list_single<int>*))
{
	timer ter;
	basic_sort bs;
	bs.generate_rand_list(nLen);
	if(bOutput)
	{	
		cout<<"before sort:"<<endl;
		bs.output_list();
	}
//
	ter.Reset();
	pf(bs.m_pSlist);
	cout<<"sort timer during nLen = "<<nLen<<" is "<<(unsigned int)ter.Interval()<<endl;
//

	if(bSortAgain)
	{
		// sort again, check timer
		ter.Reset();
		pf(bs.m_pSlist);
		cout<<"	sort timer during nLen = "<<nLen<<" is "<<(unsigned int)ter.Interval()<<endl;
	}

	if(bOutput)
	{
		cout<<"after sort:"<<endl;
		bs.output_list();
	}

	if(bNeedVerify)
	{
		// using another sort to test again
		pf2(bs.m_pSlist);
		cout<<"after test sort:"<<endl;
		bs.output_list();
	}

	bs.free_list();
};

/*static*/ void basic_sort::test_list_sort()
{
	cout<<"bubble sort:"<<endl;
//	run_one_list_sort(sing_list_sort<int>::bubble, 100, FALSE, FALSE, FALSE, NULL);
//	run_one_list_sort(sing_list_sort<int>::bubble, 200, FALSE, FALSE, FALSE, NULL);
//	run_one_list_sort(sing_list_sort<int>::bubble, 400, FALSE, FALSE, FALSE, NULL);
//	run_one_list_sort(sing_list_sort<int>::bubble, 800, FALSE, FALSE, FALSE, NULL);
//	run_one_list_sort(sing_list_sort<int>::bubble, 1600, FALSE, FALSE, FALSE, NULL);
//	run_one_list_sort(sing_list_sort<int>::bubble, 3200, FALSE, FALSE, FALSE, NULL);
// 	run_one_list_sort(sing_list_sort<int>::bubble, 6400, FALSE, FALSE, FALSE, NULL);

	cout<<"selection sort:"<<endl;
//	run_one_list_sort(sing_list_sort<int>::selection, 100, FALSE, FALSE, FALSE, NULL);
//	run_one_list_sort(sing_list_sort<int>::selection, 200, FALSE, FALSE, FALSE, NULL);
//	run_one_list_sort(sing_list_sort<int>::selection, 400, FALSE, FALSE, FALSE, NULL);
//	run_one_list_sort(sing_list_sort<int>::selection, 800, FALSE, FALSE, FALSE, NULL);
//	run_one_list_sort(sing_list_sort<int>::selection, 1600, FALSE, FALSE, FALSE, NULL);
//	run_one_list_sort(sing_list_sort<int>::selection, 3200, FALSE, FALSE, FALSE, NULL);
// 	run_one_list_sort(sing_list_sort<int>::selection, 6400, FALSE, FALSE, FALSE, NULL);
};

BOOL basic_sort::generate_rand_vector(int nLen)
{
	rand_generator rg(0, 0, 10000);
	if(nLen <= 0)
		nLen = 32;
	
	m_pVector = new _vector<int>(nLen);

	for(int i=0; i<nLen; ++i)
		m_pVector->push_back(rg.get());
	
	return TRUE;
};

void basic_sort::output_vector()
{
	if(m_pVector && m_pVector->size())
	{
		for(int i=0; i<m_pVector->size(); ++i)
		{
			cout<<(*m_pVector)[i]<<"	";
		//	if(i%10 == 9)
		//		cout<<endl;
		}
		cout<<endl;
	}
	else
	{
		cout<<"basic_sort::output_array -- no data here"<<endl;
	}
};

void basic_sort::free_vector()
{
	if(m_pVector)
	{
		delete m_pVector;
		m_pVector = DsNULL;
	}
};

BOOL basic_sort::generate_rand_list(int nLen)
{
	rand_generator rg(0, 0, 10000);
	if(nLen <= 0)
		nLen = 32;
	
	m_pSlist = new list_single<int>();

	if(!m_pSlist)
		return FALSE;

	for(int i=0; i<nLen; ++i)
	{
		m_pSlist->add(rg.get());
	}
	
	return TRUE;
};

void basic_sort::free_list()
{
	if(m_pSlist)
	{
		delete m_pSlist;
		m_pSlist = DsNULL;
	}
};

void basic_sort::output_list()
{
	if(m_pSlist && m_pSlist->size())
	{
		list_single<int>::t_pnode head = m_pSlist->get_head();
		while(head)
		{
			cout<<head->get_data()<<"	";
			head = head->get_next();
		}
		cout<<endl;
	}
	else
	{
		cout<<"basic_sort::output_list -- no data here"<<endl;
	}
};