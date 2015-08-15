#include "queue_use.h"

void adt_queue_usage::str_to_output(char* str)
{
	int nStrLen = 0;
	if(!str)
	{
		cout<<"Error! adt_queue_usage::str_to_output NULL pointer as input!"<<endl;
		return;
	}
	nStrLen = strlen(str);
	if(0 == nStrLen)
	{
		cout<<"Error! adt_queue_usage::str_to_output input string is empty!"<<endl;
		return;
	}

	cout<<"Input string is: "<<str<<endl;

	//iqueue<char>* pQueue = new queue_array<char>(32);
	iqueue<char>* pQueue = new queue_list_double<char>();
	//iqueue<char>* pQueue = new queue_list_single<char>();
	while(*str != '\0')
	{
		if(*str == '*')
		{
			cout<<"	**	output "<<pQueue->get()<<endl;
		}
		else 
		{
//			cout<<"	**	input "<<*str<<endl;
			pQueue->put(*str);
		}
		++str;
	}
	delete pQueue;
}