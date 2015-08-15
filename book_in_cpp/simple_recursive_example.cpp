#include "simple_recursive_example.h"

int widgets_recursive::calc_prefix_expression(char* prefix, int& pos)
{
	int nRet = 0;
	while(prefix[pos] == ' ')
		++pos;
	if(prefix[pos] == '+')
	{
		++pos;
		return calc_prefix_expression(prefix, pos)+
			calc_prefix_expression(prefix, pos);
	}
	else if(prefix[pos] == '*')
	{
		++pos;
		return calc_prefix_expression(prefix, pos)*
			calc_prefix_expression(prefix, pos);
	}
	while(prefix[pos] >= '0' && prefix[pos] <= '9')
	{
		nRet = 10*nRet + prefix[pos]-'0';
		++pos;
	}
	return nRet;
};

double widgets_recursive::calc_log_n_factorial(int n)
{
	if(n<=1)
		return 0;
	else
		return log10((double)n)+calc_log_n_factorial(n-1);
}

int widgets_recursive::hanoitower(int nLevel)
{
	if(nLevel <= 0)
		return 0;

	int from=0, to=2, platform=1;
	return move_to_tower(nLevel, 0, 2, 1);
};

int widgets_recursive::move_to_tower(int nLevel, int from, int to, int platform)
{
	int nSteps = 0;
	if(nLevel > 1)
	{
		nSteps = move_to_tower(nLevel-1, from, platform, to);
		nSteps += move_to_tower(1, from, to, platform);
		nSteps += move_to_tower(nLevel-1, platform, to, from);
	}
	else// if(nLevel == 1)
	{
	//	cout<<"Move: from "<<from<<" to "<<to<<endl;
		nSteps = 1;
	}

	return nSteps;
};

int widgets_recursive::fibonaci(int n)
{
	static int no_known[45] = {0};
	if(no_known[n] != 0)
		return no_known[n];
	if(n<0 || n>45)
		return 0;
	if(n==0 || n==1)
	{
		no_known[n] = 1;
		return no_known[n];
	}
	else
	{
		int nRet = fibonaci(n-1)+fibonaci(n-2);
		no_known[n] = nRet;
		return nRet;
	}
};