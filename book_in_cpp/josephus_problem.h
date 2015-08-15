#ifndef _INCLUDED_JOSEPHUS_PROBLEM_H_
#define _INCLUDED_JOSEPHUS_PROBLEM_H_

#include "platform.h"

class josephus_problem
{
public:
	class people_node{
	public:
		people_node():m_num(0),m_next(DsNULL){};
		people_node(int num, people_node* pNext):m_num(num),m_next(pNext){};
		virtual ~people_node(){};
		void set_num(int num){m_num = num;};
		void set_next(people_node* pNext){m_next = pNext;};
		int get_num() { return m_num;};
		people_node* get_next() {return m_next;};
	protected:
		int		m_num;
		people_node* m_next;
	};

	static void get_last_one(int total, int mod);
};
#endif //_INCLUDED_JOSEPHUS_PROBLEM_H_