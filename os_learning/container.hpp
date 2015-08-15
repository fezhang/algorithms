#ifndef _INCLUDED_CONTAINER_HPP_
#define _INCLUDED_CONTAINER_HPP_

template <typename Item>
class icontainer
{
public:
	virtual void push_front(Item) = 0;
	virtual Item pop_front() = 0;
	virtual void push_back(Item) = 0;
	virtual Item pop_back() = 0;
	virtual int size() = 0;
	virtual Item& operator[](int nIndex) = 0;
};
#endif //_INCLUDED_CONTAINER_HPP_