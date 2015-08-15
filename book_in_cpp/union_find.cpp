#include "union_find.h"

union_find::union_find()
:m_begin(INVALID_DS_SIZE),m_end(INVALID_DS_SIZE)
{
};

union_find::~union_find()
{
};

void union_find::set_begin_end(const int begin, const int end)
{
	m_begin = begin;
	m_end = end;
};

int& union_find::get_begin()
{
	return m_begin;
};

int& union_find::get_end()
{
	return m_end;
};

bool union_find::valid_pair(const int first, const int second)
{
	if (first<m_begin || first>m_end
		|| second<m_begin || second>m_end)
		return false;
	else
		return true;
};

void union_find::inseart_pair(const int first, const int second)
{
	cout<<"inseart pair here!"<<endl;
};

bool union_find::check_pair(const int first, const int second)
{
	cout<<"check if pair exist. now always return true."<<endl;
	return true;
};

//////////////////////////////////////////////////////////////////////////
// Implementation of class uf_array

uf_array::uf_array()
:m_base(DsNULL),m_len(0)
{
};

uf_array::~uf_array()
{
	if(m_base)
		delete[] m_base;
	m_base = DsNULL;
	m_len = 0;
};

void uf_array::set_begin_end(const int begin, const int end)
{
	if(m_base)
		delete [] m_base;
	m_base = DsNULL;
	m_len = 0;

	union_find::set_begin_end(begin, end);
	if(begin > end)
	{
		m_begin = end;
		m_end = begin;
	}
	m_len = m_end-m_begin+1;
	m_base = new int[m_len];
	if(!m_base)
	{
		cout<<"Error, not enough memory!"<<endl;
		return;
	}
	for( int i=0; i<m_len; ++i)
	{
		m_base[i] = m_begin+i;
	}
};

void uf_array::inseart_pair(const int first, const int second)
{
	if(!m_base)
		return;
	int nFirst = m_base[first-m_begin];
	for(int i=0; i<m_len;++i)
	{
		if(m_base[i] == nFirst)
			m_base[i] = m_base[second-m_begin];
	}
};

bool uf_array::check_pair(const int first, const int second)
{
	if(!m_base)
		return false;
	if(m_base[first-m_begin] == m_base[second-m_begin])
		return true;
	else
	{
		inseart_pair(first, second);
		return false;
	}
};

void uf_array::DUMP()
{
	if(!m_base)
		return;
	for(int i=0; i<m_len; ++i)
	{
		cout<<m_base[i]<<" ";
		if(i%12 == 11)
			cout<<endl;
	}
	cout<<endl;
}
// End of class uf_array
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Implementation of class uf_quick_tree

uf_quick_tree::uf_quick_tree()
:m_base(DsNULL), m_len(0)
{
};

uf_quick_tree::~uf_quick_tree()
{
	if(m_base)
		delete[] m_base;
	m_base = DsNULL;
	m_len = 0;
};

void uf_quick_tree::set_begin_end(const int begin, const int end)
{
	if(m_base)
		delete [] m_base;
	m_base = DsNULL;
	m_len = 0;

	union_find::set_begin_end(begin, end);
	if(begin > end)
	{
		m_begin = end;
		m_end = begin;
	}

	m_len = m_end-m_begin+1;
	m_base = new int[m_len];
	if(!m_base)
	{
		cout<<"Error, not enough memory!"<<endl;
		return;
	}
	for( int i=0; i<m_len; ++i)
	{
		m_base[i] = i;
	}
};

void uf_quick_tree::inseart_pair(const int first, const int second)
{
	if(!m_base)
		return;
	m_base[first-m_begin] = second-m_begin;
	return;
};

bool uf_quick_tree::check_pair(const int first, const int second)
{
	int nRootFirst = -1;
	int nRootSecond = -1;
	for(nRootFirst=m_base[first-m_begin];
		nRootFirst!=m_base[nRootFirst];
		nRootFirst = m_base[nRootFirst]
		);
	for(nRootSecond=m_base[second-m_begin];
		nRootSecond!=m_base[nRootSecond];
		nRootSecond = m_base[nRootSecond]
		);
	if(nRootFirst==nRootSecond)
		return true;
	else
	{
		inseart_pair(nRootFirst, nRootSecond);
		return false;
	}
};

void uf_quick_tree::DUMP()
{
	if(!m_base)
		return;
	for(int i=0; i<m_len; ++i)
	{
		cout<<m_base[i]<<" ";
		if(i%12 == 11)
			cout<<endl;
	}
	cout<<endl;
};

// End of class uf_quick_tree
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Implementaion of class uf_weight_tree

uf_weight_tree::uf_weight_tree()
:m_base(DsNULL),m_weight(DsNULL),m_len(0)
{
};

uf_weight_tree::~uf_weight_tree()
{
	if(m_base)
		delete[] m_base;
	if(m_weight)
		delete[] m_weight;
	
	m_base = DsNULL;
	m_weight = DsNULL;
	m_len = 0;
};

void uf_weight_tree::set_begin_end(const int begin, const int end)
{
	if(m_base)
		delete[] m_base;
	if(m_weight)
		delete[] m_weight;
	
	m_base = DsNULL;
	m_weight = DsNULL;
	m_len = 0;

	union_find::set_begin_end(begin, end);
	if(begin>end)
	{
		m_begin = end;
		m_end = begin;
	}

	m_len = m_end-m_begin+1;
	m_base = new int[m_len];
	m_weight = new int[m_len];
	if(!m_base || !m_weight)
	{
		cout<<"Error,not enough memory!"<<endl;
		return;
	}

	for(int i=0; i<m_len; ++i)
	{
		m_base[i] = i;
		m_weight[i] = 1;
	}
};

void uf_weight_tree::inseart_pair(const int first, const int second)
{
	if(!m_base || !m_weight)
		return;

	if(m_weight[first] < m_weight[second])
	{
		m_base[first] = second;
		m_weight[first] += m_weight[second];
	}
	else
	{
		m_base[second] = first;
		m_weight[second] += m_weight[first];
	}
};

bool uf_weight_tree::check_pair(const int first, const int second)
{
	int nRootFirst = -1;
	int nRootSecond = -1;
	for(nRootFirst=m_base[first-m_begin];
		nRootFirst!=m_base[nRootFirst];
		nRootFirst = m_base[nRootFirst]
		);
	for(nRootSecond=m_base[second-m_begin];
		nRootSecond!=m_base[nRootSecond];
		nRootSecond = m_base[nRootSecond]
		);
	if(nRootFirst==nRootSecond)
		return true;
	else
	{
		inseart_pair(nRootFirst, nRootSecond);
		return false;
	}
};

// End of class uf_weight_tree
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Implementation of class uf_compression_weight_tree

uf_compression_weight_tree::uf_compression_weight_tree()
{
};

uf_compression_weight_tree::~uf_compression_weight_tree()
{
};

bool uf_compression_weight_tree::check_pair(const int first, const int second)
{
	int nRootFirst = -1;
	int nRootSecond = -1;
	for(nRootFirst=m_base[first-m_begin];
		nRootFirst!=m_base[nRootFirst];
		nRootFirst = m_base[nRootFirst]
		)
		m_base[nRootFirst]=m_base[m_base[nRootFirst]];

	for(nRootSecond=m_base[second-m_begin];
		nRootSecond!=m_base[nRootSecond];
		nRootSecond = m_base[nRootSecond]
		)
		m_base[nRootSecond]=m_base[m_base[nRootSecond]];

	if(nRootFirst==nRootSecond)
		return true;
	else
	{
		inseart_pair(nRootFirst, nRootSecond);
		return false;
	}	
};

// End of class uf_compression_weight_tree
//////////////////////////////////////////////////////////////////////////