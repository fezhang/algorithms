#include "connectivity.h"

connectivity::connectivity()
:m_union_find(DsNULL)
{
};

connectivity::~connectivity()
{
};

void connectivity::run()
{
	if(!check_object_is_valid())
	{
		cout<<"There is no algorithm executor! Please set it first and run again!"<<endl;
		return;
	}
	cout<<"Please input two integer between "<<m_union_find->get_begin()
		<<" and "<<m_union_find->get_end()<<";"<<endl;
	cout<<"If you want to quit the process please input "<<
		m_union_find->get_begin()-1<<"."<<endl;
	int first = 0, next = 0;
	while (1)
	{
		input_result res = get_pair(first, next);
		if(res_ok == res)
		{
			timer tmer;
			tmer.Reset();
			//
			bool bPairExist = is_pair_exist(first,next);
			//
			int len = tmer.Interval();
			cout<<"interval is: "<<len<<endl;
			if(!bPairExist)
				output_pair(first,next);
			else
				cout<<"Pair "<<first<<","<<next<<" exist!"<<endl;
		}
		else if(res_fail == res)
		{
			continue;
		}
		else if(res_quit == res)
			break;
	}
};

connectivity::input_result connectivity::get_pair(int& first,  int& next)
{
	if(!check_object_is_valid())
	{
		cout<<"There is no algorithm executor! Please set it first and run again!"<<endl;
		return res_quit;
	}

	cin>>first;
	if(m_union_find->get_begin()-1 == first)
		return res_quit;
	cin>>next;
	// check first and next
	if (!m_union_find->valid_pair(first, next))
	{
		cout<<"Sorry, please input number between "<<m_union_find->get_begin()
			<<" and "<<m_union_find->get_end()<<";"<<endl;
		cout<<"Please input them again!"<<endl;
		return res_fail;
	}
	else
		return res_ok;
};

void connectivity::output_pair(const int& first, const int& next)
{
	cout<<first<<","<<next<<endl;
};

bool connectivity::is_pair_exist(int& first, int& next)
{
	if(check_object_is_valid())
		return m_union_find->check_pair(first, next);
	else
		return false;
};

void connectivity::set_union_find_object(union_find* uf)
{
	m_union_find = uf;
};

void connectivity::set_begin_end(const int& begin, const int& end)
{
	if(m_union_find)
	{
		m_union_find->set_begin_end(begin, end);
	}
};

bool connectivity::check_object_is_valid()
{
	if(!m_union_find)
		return false;
	else if(INVALID_DS_SIZE == m_union_find->get_begin()
		|| INVALID_DS_SIZE == m_union_find->get_end())
		return false;
	else
		return true;
};
