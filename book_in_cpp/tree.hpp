#ifndef _INCLUDED_TREE_HPP_
#define _INCLUDED_TREE_HPP_

#include "platform.h"
#include "obj_interface.hpp"
#include "queue.hpp"

template <typename Item> class bin_tree_node;
template <typename Item> class bin_tree;
template <typename Item> class ibin_tree_traveler;
template <typename Item> class tree_traveler_output; //public ibin_tree_traveler

//////////////////////////////////////////////////////////////////////////
// interface ibin_tree_traveler
template <typename Item>
class ibin_tree_traveler
{
public:
	typedef bin_tree_node<Item>		t_node;
	typedef bin_tree_node<Item>*	t_pnode;
public:
	virtual void travel(t_pnode) = 0;
	virtual void start() = 0;
	virtual void end() = 0;
};


//////////////////////////////////////////////////////////////////////////
// class bin_tree_node

template <typename Item>
class bin_tree_node
{
public:
	typedef bin_tree_node<Item>		t_node;
	typedef bin_tree_node<Item>*	t_pnode;
	typedef ibin_tree_traveler<Item>* t_ptravelor;

public:
	bin_tree_node();
	bin_tree_node(Item data, t_pnode parent = DsNULL,
		t_pnode lChild = DsNULL, t_pnode rChild = DsNULL);
	bin_tree_node(t_node&);	//only copy this node
	t_node& operator=(t_node&);	//only assignment this node
	virtual ~bin_tree_node();

public:
	Item&	get_data();
	t_pnode get_parent();
	t_pnode get_lchild();
	t_pnode get_rchild();
	
	void set_data(Item);
	void set_parent(t_pnode);
	void set_lchild(t_pnode);
	void set_rchild(t_pnode);

	DsBOOL has_children();
public:
	t_pnode add_lchild(Item);
	t_pnode add_rchild(Item);
	void remove_lchild();
	void remove_rchild();

	void travel_RootLR(t_ptravelor);
	void travel_LRRoot(t_ptravelor);
	void travel_LRootR(t_ptravelor);
	void travel_level(t_ptravelor);
	
	t_pnode clone();
protected:
	Item		m_data;
	t_pnode		m_pLChild;
	t_pnode		m_pRChild;
	t_pnode		m_pParent;
};

template <typename Item>
bin_tree_node<Item>::bin_tree_node()
:m_data(),m_pLChild(DsNULL), m_pRChild(DsNULL),m_pParent(DsNULL)
{
};

template <typename Item>
bin_tree_node<Item>::bin_tree_node(
		Item data, 
		bin_tree_node<Item>* parent,
		bin_tree_node<Item>* lChild, 
		bin_tree_node<Item>* rChild)
		:m_data(data), m_pLChild(lChild),m_pRChild(rChild),m_pParent(parent)
{
};

template <typename Item>
bin_tree_node<Item>::bin_tree_node(bin_tree_node<Item>& rhs)
:	m_data(rhs.get_data()), 
	m_pLChild(rhs.get_lchild()),
	m_pRChild(rhs.get_rchild()),
	m_pParent(rhs.get_parent())
{
};

template <typename Item>
bin_tree_node<Item>& bin_tree_node<Item>::operator=(bin_tree_node<Item>& rhs)
{
	if(&rhs == this)
		return *this;

	set_data(rhs.get_data());
	set_lchild(DsNULL);
	set_rchild(DsNULL);
	set_parent(DsNULL);
	
	return *this;
};

template <typename Item>
bin_tree_node<Item>::~bin_tree_node()
{
	remove_lchild();
	remove_rchild();
};

template <typename Item>
Item&	bin_tree_node<Item>::get_data()
{
	return m_data;
};

template <typename Item>
bin_tree_node<Item>* bin_tree_node<Item>::get_parent()
{
	return m_pParent;
};

template <typename Item>
bin_tree_node<Item>* bin_tree_node<Item>::get_lchild()
{
	return m_pLChild;
};

template <typename Item>
bin_tree_node<Item>* bin_tree_node<Item>::get_rchild()
{
	return m_pRChild;
};

template <typename Item>	
void bin_tree_node<Item>::set_data(Item data)
{
	m_data = data;
};

template <typename Item>
void bin_tree_node<Item>::set_parent(bin_tree_node<Item>* parent)
{
	m_pParent = parent;
};

template <typename Item>
void bin_tree_node<Item>::set_lchild(bin_tree_node<Item>* lchild)
{
	m_pLChild = lchild;
};

template <typename Item>
void bin_tree_node<Item>::set_rchild(bin_tree_node<Item>* rchild)
{
	m_pRChild = rchild;
};

template <typename Item>
DsBOOL bin_tree_node<Item>::has_children()
{
	if(m_pLChild || m_pRChild)
		return DsTRUE;
	else
		return DsFALSE;
};

template <typename Item>
bin_tree_node<Item>* bin_tree_node<Item>::add_lchild(Item data)
{
	remove_lchild();
	typedef bin_tree_node<Item>* pnode;
	typedef bin_tree_node<Item>::t_node node;
	pnode lchild = new node(data, this, DsNULL, DsNULL);
	m_pLChild = lchild;
	return lchild;
};

template <typename Item>
bin_tree_node<Item>* bin_tree_node<Item>::add_rchild(Item data)
{
	remove_rchild();
	typedef bin_tree_node<Item>* pnode;
	typedef bin_tree_node<Item>::t_node node;
	pnode rchild = new node(data, this, DsNULL, DsNULL);
	m_pRChild = rchild;
	return rchild;
};

template <typename Item>
void bin_tree_node<Item>::remove_lchild()
{
	typedef bin_tree_node<Item>* pnode;
	pnode lchild = m_pLChild;
	m_pLChild = DsNULL;
	
	if(lchild)
	{
		lchild->remove_lchild();
		lchild->remove_rchild();
		delete lchild;
	}
};

template <typename Item>
void bin_tree_node<Item>::remove_rchild()
{
	typedef bin_tree_node<Item>* pnode;
	pnode rchild = m_pRChild;
	m_pRChild = DsNULL;
	
	if(rchild)
	{
		rchild->remove_lchild();
		rchild->remove_rchild();
		delete rchild;
	}
};
template <typename Item>
void bin_tree_node<Item>::travel_RootLR(ibin_tree_traveler<Item>* tor)
{
	if(!tor)
		return;

	tor->travel(this);
	if(get_lchild())
		get_lchild()->travel_RootLR(tor);
	if(get_rchild())
		get_rchild()->travel_RootLR(tor);
};

template <typename Item>
void bin_tree_node<Item>::travel_LRRoot(ibin_tree_traveler<Item>* tor)
{
	if(!tor)
		return;

	if(get_lchild())
		get_lchild()->travel_LRRoot(tor);
	if(get_rchild())
		get_rchild()->travel_LRRoot(tor);
	tor->travel(this);
};

template <typename Item>
void bin_tree_node<Item>::travel_LRootR(ibin_tree_traveler<Item>* tor)
{
	if(!tor)
		return;

	if(get_lchild())
		get_lchild()->travel_LRootR(tor);
	
	tor->travel(this);

	if(get_rchild())
		get_rchild()->travel_LRootR(tor);
};

template <typename Item>
void bin_tree_node<Item>::travel_level(ibin_tree_traveler<Item>* tor)
{
	if(!tor)
		return;

	queue_list_double<bin_tree_node<Item>*> qld;
	bin_tree_node<Item>* pTemp = NULL;
	qld.put(this);
	while(!qld.empty())
	{
		pTemp = qld.get();
		tor->travel(pTemp);
		if(pTemp->get_lchild())
			qld.put(pTemp->get_lchild());
		if(pTemp->get_rchild())
			qld.put(pTemp->get_rchild());
	}
	return;
};

template <typename Item>
bin_tree_node<Item>* bin_tree_node<Item>::clone()
{
	bin_tree_node<Item>* pRet = new bin_tree_node<Item>::t_node(m_data);
	if(get_lchild())
		pRet->set_lchild(get_lchild()->clone());
	if(get_rchild())
		pRet->set_rchild(get_rchild()->clone());

	return pRet;
};

// End of bin_tree_node
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// class bin_tree

template <typename Item>
class bin_tree
{
public:
	typedef bin_tree_node<Item>		t_node;
	typedef bin_tree_node<Item>*	t_pnode;
	typedef bin_tree<Item>			t_tree;
	typedef bin_tree<Item>*			t_ptree;
	typedef ibin_tree_traveler<Item>* t_ptravelor;

public:
	bin_tree();
	bin_tree(Item);
	bin_tree(t_tree&);	//copy the tree root
	bin_tree(t_pnode);	//name changed, recursive foundation
	virtual ~bin_tree();
	t_tree& operator=(t_tree&);	//copy a tree
	
	t_tree* clone();
public:
	DsBOOL empty();
	DsBOOL has_children();
	void add_lchild(t_tree&);
	void add_rchild(t_tree&);
	void remove_lchild();
	void remove_rchild();

	void clear_all_children();
	t_pnode get_lchild();
	t_pnode get_rchild();

	void travel_RootLR(t_ptravelor);
	void travel_LRRoot(t_ptravelor);
	void travel_LRootR(t_ptravelor);
	void travel_level(t_ptravelor);

public:
	t_pnode	m_root;
};

template <typename Item>
bin_tree<Item>::bin_tree()
:m_root(DsNULL)
{
	m_root = new bin_tree<Item>::t_node();
};

template <typename Item>
bin_tree<Item>::bin_tree(Item)
:m_root(DsNULL)
{
	m_root = new bin_tree<Item>::t_node(Item);
};

template <typename Item>
bin_tree<Item>::bin_tree(bin_tree<Item>& rhs)
{
	m_root = rhs.m_root;
	rhs.m_root = DsNULL;
};

template <typename Item>
bin_tree<Item>::bin_tree(bin_tree_node<Item>* node)	//name changed, recursive foundation
{
	m_root = node;
};

template <typename Item>
bin_tree<Item>::~bin_tree()
{
	if(m_root)
	{
		clear_all_children();
		delete m_root;
	}
};

template <typename Item>
bin_tree<Item>& bin_tree<Item>::operator=(bin_tree<Item>& rhs)	//copy a tree
{
	if(&rhs == this)
		return *this;

	if(m_root)
	{
		clear_all_children();
		delete m_root;
	}

	m_root = rhs.m_root;
	rhs.m_root = DsNULL;
	return *this;
};

template <typename Item>
bin_tree<Item>* bin_tree<Item>::clone()
{
	bin_tree<Item>* pTreeRet = DsNULL;
	if(m_root == DsNULL)
		return DsNULL;

	bin_tree_node<Item>* pRoot = m_root->clone();
	pTreeRet = new bin_tree<Item>(pRoot);

	return pTreeRet;
};

template <typename Item>
DsBOOL bin_tree<Item>::empty()
{
	if(m_root == DsNULL)
		return DsTRUE;
	else
		return DsFALSE;
};

template <typename Item>
DsBOOL bin_tree<Item>::has_children()
{
	if(!empty())
	{
		if(m_root->get_lchild() || m_root->get_rchild())
			return DsTRUE;
	}

	return DsFALSE;
};

template <typename Item>
void bin_tree<Item>::add_lchild(bin_tree<Item>& tree)
{
	if(m_root)
	{
		if(m_root->get_lchild() != DsNULL)
		{
			delete m_root->get_lchild();
		}
	}
	else
	{
		m_root = new bin_tree<Item>::t_node();
	}

	m_root->set_lchild(tree.m_root);
	tree.m_root = DsNULL;
};

template <typename Item>
void bin_tree<Item>::add_rchild(bin_tree<Item>& tree)
{
	if(m_root)
	{
		if(m_root->get_rchild() != DsNULL)
		{
			delete m_root->get_rchild();
		}
	}
	else
	{
		m_root = new bin_tree<Item>::t_node();
	}

	m_root->set_rchild(tree.m_root);
	tree.m_root = DsNULL;
};

template <typename Item>
void bin_tree<Item>::remove_lchild()
{
	if(m_root && m_root->get_lchild())
	{
		delete m_root->get_lchild();
		m_root->set_lchild(DsNULL);
	}
	return;
};

template <typename Item>
void bin_tree<Item>::remove_rchild()
{
	if(m_root && m_root->get_rchild())
	{
		delete m_root->get_rchild();
		m_root->set_rchild(DsNULL);
	}
	return;
};

template <typename Item>
void bin_tree<Item>::clear_all_children()
{
	if(m_root)
	{
		remove_lchild();
		remove_rchild();
	}
};

template <typename Item>
bin_tree_node<Item>* bin_tree<Item>::get_lchild()
{
	bin_tree_node<Item>* pNodeRet = DsNULL;
	if(m_root)
	{
		pNodeRet = m_root->get_lchild();
	}
	return pNodeRet;
};

template <typename Item>
bin_tree_node<Item>* bin_tree<Item>::get_rchild()
{	
	bin_tree_node<Item>* pNodeRet = DsNULL;
	if(m_root)
	{
		pNodeRet = m_root->get_rchild();
	}
	return pNodeRet;
};

template <typename Item>
void bin_tree<Item>::travel_RootLR(ibin_tree_traveler<Item>* tor)
{
	if(!tor)
		return;

	tor->start();
	if(m_root)
		m_root->travel_RootLR(tor);
	tor->end();
};

template <typename Item>
void bin_tree<Item>::travel_LRRoot(ibin_tree_traveler<Item>* tor)
{
	if(!tor)
		return;

	tor->start();
	if(m_root)
		m_root->travel_LRRoot(tor);	
	tor->end();
};

template <typename Item>
void bin_tree<Item>::travel_LRootR(ibin_tree_traveler<Item>* tor)
{
	if(!tor)
		return;

	tor->start();
	if(m_root)
		m_root->travel_LRootR(tor);	
	tor->end();
};

template <typename Item>	
void bin_tree<Item>::travel_level(ibin_tree_traveler<Item>* tor)
{
	if(!tor)
		return;

	tor->start();
	if(m_root)
		m_root->travel_level(tor);
	tor->end();
};

// End of bin_tree
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// tree_traveler_output
template <typename Item>
class tree_traveler_output: public ibin_tree_traveler<Item>
{
public:
	virtual void travel(t_pnode);
	virtual void start();
	virtual void end();
};

template <typename Item>
void tree_traveler_output<Item>::travel(t_pnode pNode)
{
	if(pNode)
	{
		cout<<pNode->get_data();
	}
};

template <typename Item>
void tree_traveler_output<Item>::start()
{
};

template <typename Item>
void tree_traveler_output<Item>::end()
{
	cout<<endl;
};
// End of tree_traveler_output
//////////////////////////////////////////////////////////////////////////
#endif //_INCLUDED_TREE_HPP_