#include "elementary_data_structure_test.h"

void elementary_data_structure_testee::execute()
{
	timer_mgr* tmmgr = timer_mgr::get_mgr();
//	if(tmmgr)
//		tmmgr->add_item("below test is for generate primaries:", 0);
//	get_primary::output_primaries(100);
//	get_primary::output_primaries(1000);
//	get_primary::output_primaries(10000);
//	get_primary::output_primaries(20000);
	if(tmmgr)
		tmmgr->add_item("below test is for Josephus problem:", 0);
	josephus_problem::get_last_one(10000, 50);
	josephus_problem::get_last_one(10000, 200);
	josephus_problem::get_last_one(10000, 800);
	josephus_problem::get_last_one(10000, 3200);
}
