#include "algorithm_analysis_test.h"

void algorithm_analysis_testee::execute()
{
	int interval = 0;
	// 100
	interval = execises_P33::e2_2(100);
	cout<<"N=100, interval="<<interval<<endl;
	// 200
	interval = execises_P33::e2_2(200);
	cout<<"N=200, interval="<<interval<<endl;
	// 400
	interval = execises_P33::e2_2(400);
	cout<<"N=400, interval="<<interval<<endl;
	// 800
	interval = execises_P33::e2_2(800);
	cout<<"N=800, interval="<<interval<<endl;

	return;
}