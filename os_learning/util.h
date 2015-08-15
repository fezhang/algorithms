#ifndef _INCLUDED_UTIL_H_
#define _INCLUDED_UTIL_H_

#include <time.h>
#include <stdlib.h>

template <typename T>
void Exchange(T& item1, T& item2)
{
	T temp = item1;
	item1 = item2;
	item2 = temp;
}

class rand_generator
{
public:
	rand_generator(int start, int end)
	{ 
		srand((UINT32)time(NULL));

		if(start>end)
			Exchange(start, end);

		m_nStart = start;
		m_nEnd = end;
	};

	int	get()
	{
		return m_nStart+rand()%(m_nEnd-m_nStart+1);
	};

    int	get(int start, int end)
	{
        if(start>end)
			Exchange(start, end);

		return start+rand()%(end-start+1);
	};

	virtual ~rand_generator(){};
protected:
	int		m_nStart;
	int		m_nEnd;
};

#endif //_INCLUDED_UTIL_H_