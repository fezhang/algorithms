#include "test_entry.h"

int main()
{
	timer_mgr* tmmgr = timer_mgr::get_mgr(20);
	tester tt;

//	connectivity_testee ctee;
//	tt.set_testee(&ctee);

//	algorithm_analysis_testee aatee;
//	tt.set_testee(&aatee);

//	elementary_data_structure_testee edstee;
//	tt.set_testee(&edstee);

//	adt_testee adttee;
//	tt.set_testee(&adttee);
	
	sort_testee sorttee;
	tt.set_testee(&sorttee);

	tt.run();
	tmmgr->output();

	timer_mgr::free_mgr();

// See below "bug", hoho why -1>5?
//	int a[] = {1,2,3,4,5};
//	cout<<sizeof(a)/sizeof(a[0])<<endl;
//	cout<<(-1>(sizeof(a)/sizeof(a[0])))<<endl;
//	cout<<(-1<(sizeof(a)/sizeof(a[0])))<<endl;
// End

	return 0;
}