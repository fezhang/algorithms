#include "josephus_problem.h"

void josephus_problem::get_last_one(int total, int mod)
{
	// check parameters
	if (total <= 1)
	{
		cout<<" Parameter total user should greater than 1!"<<endl;
		return;
	}
	if (mod >= total)
	{
		cout<<" Parameter mod should be greater than taotal!"<<endl;
		return;
	}
	
	// initialize the people list
	people_node* head = new people_node(0, DsNULL);
	head->set_next(head); // point to myself
	people_node* pTail = head;
	for(int i=0; i<total-1; ++i)
	{
		people_node* pAdded = new people_node(i, head);
		pTail->set_next(pAdded);
		pTail = pAdded;
	}

	// remove users
	pTail = head;
	int nForLoopStep = 0;

	timer ter;
	ter.Reset();

	while (pTail != pTail->get_next())
	{
		for(int i=1;i< mod; ++i)
		{
			pTail = pTail->get_next();
			++nForLoopStep;
		}
		people_node* pToBeRemoved = pTail->get_next();
		pTail->set_next(pToBeRemoved->get_next());
		delete pToBeRemoved;
	}

	int length = ter.Interval();
	timer_mgr* termgr = timer_mgr::get_mgr();
	if(termgr)
	{
		char szTemp[100] = {0};
		sprintf(szTemp, "During total=%d,mod=%d,for loop step=%d,", total, mod, nForLoopStep);
		termgr->add_item(szTemp, length);
	}
	
	//output last user
	cout<<"last user is "<<pTail->get_num()<<endl;
	delete pTail;
	return;
};