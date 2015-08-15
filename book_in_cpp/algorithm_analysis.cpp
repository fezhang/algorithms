#include "algorithm_analysis.h"

int execises_P33::e2_2(int N)
{
	timer ter;
	int n = 0;
	ter.Reset();
	for (int i=0; i<N; ++i)
		for (int j=0; j<N; ++j)
			for (int k=0; k<N; ++k)
				++n;
	return ter.Interval();
};