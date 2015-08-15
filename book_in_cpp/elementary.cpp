#include "elementary.h"

void get_primary::output_primaries(int N)
{
	if(N<=0)
		N = 1000;
	int i = 0;
	int* pArray = new int[N];
	if (!pArray)
	{
		cout<<"Error! Not enough memory!"<<endl;
		return;
	}
	for(i=2; i<N; ++i)
		pArray[i] = 1;
//
	timer ter;
	ter.Reset();
//
	for(i=2; i<N; ++i)
	{
		if(pArray[i])
		{
			for(int j=i;j*i<N;++j)
				pArray[i*j] = 0;
		}
	}
//
	int interval = ter.Interval();
	timer_mgr* tmmgr = timer_mgr::get_mgr();
	char szTmp[40] = {0};
	sprintf(szTmp,"N=%d",N);
	if(tmmgr)
		tmmgr->add_item(szTmp, interval);
//
	int nOut = 0;
	for(i=2; i<N; ++i)
	{
		if(pArray[i])
		{
			++nOut;
			cout<<i<<" ";
			if(nOut%10 == 9)
				cout<<endl;
		}
	}
	cout<<endl;
	
	delete[] pArray;
	return;
}

