#include "tree_use.h"

void tree_usage::test_tree_interface()
{
	//test_tree_node();
	//test_ctor_dtor();
	test_tree_generator();
};

void tree_usage::test_tree_node()
{
	bin_tree_node<int>* btn = new bin_tree_node<int>();
	btn->set_data(1);
	btn->add_lchild(2);
	btn->add_rchild(3);
	
	bin_tree_node<int>* plchild = btn->get_lchild();
	bin_tree_node<int>* prchild = btn->get_rchild();

	plchild->add_lchild(4);
	plchild->add_rchild(5);
	
	tree_traveler_output<int> tto;
	cout<<"travel root l r:"<<endl;
	btn->travel_RootLR(&tto);
	cout<<"travel l r root:"<<endl;
	btn->travel_LRRoot(&tto);
	cout<<"travel l root r:"<<endl;
	btn->travel_LRootR(&tto);
	cout<<"travel level:"<<endl;
	btn->travel_level(&tto);

	bin_tree_node<int>* btn2 = btn->clone();
	cout<<"travel root l r:"<<endl;
	btn2->travel_RootLR(&tto);
	cout<<"travel l r root:"<<endl;
	btn2->travel_LRRoot(&tto);
	cout<<"travel l root r:"<<endl;
	btn->travel_LRootR(&tto);
	cout<<"travel level:"<<endl;
	btn2->travel_level(&tto);
	
	delete btn2;
	delete btn;
};

void tree_usage::test_ctor_dtor()
{
	bin_tree_node<int>* btn = new bin_tree_node<int>();
	btn->set_data(1);
	btn->add_lchild(2);
	btn->add_rchild(3);
	
	bin_tree_node<int>* plchild = btn->get_lchild();
	bin_tree_node<int>* prchild = btn->get_rchild();

	plchild->add_lchild(4);
	plchild->add_rchild(5);

	bin_tree<int> bt(btn);
	tree_traveler_output<int> tto;
	cout<<"travel root l r:"<<endl;
	bt.travel_RootLR(&tto);
	cout<<"travel l r root:"<<endl;
	bt.travel_LRRoot(&tto);
	bt.travel_level(&tto);
	
	bin_tree<int>::t_ptree pAnotherTree = bt.clone();
	cout<<"travel root l r:"<<endl;
	pAnotherTree->travel_RootLR(&tto);
	cout<<"travel l r root:"<<endl;
	pAnotherTree->travel_LRRoot(&tto);
	pAnotherTree->travel_level(&tto);

	delete pAnotherTree;
};

void tree_usage::test_tree_generator()
{
	tree_traveler_output<char> tto;
	char preorder[] = "EDBACHFG";
	char inorder[] = "ABCDEFGH";
	bin_tree<char>* pTree = generate_tree(preorder, inorder, 8);
	if(pTree)
	{
		cout<<"level travel result:	";
		pTree->travel_level(&tto);
		cout<<"preorder travel result:	";
		pTree->travel_RootLR(&tto);
		cout<<"inorder travel result:	";
		pTree->travel_LRootR(&tto);
	}
	else
	{
		cout<<"fail to generate tree!"<<endl;
	}

	delete pTree;
	return;
};

bin_tree<char>* tree_usage::generate_tree(char* preorder, char* inorder, int nLen)
{
	bin_tree<char>* pRet = NULL;
	bin_tree_node<char>* pRoot = 
		generate_node(preorder, inorder, nLen);
	if(pRoot)
	{
		pRet = new bin_tree<char>(pRoot);
	}
	return pRet;
};

bin_tree_node<char>* tree_usage::generate_node(char* preorder, char* inorder, int nLen)
{
	bin_tree_node<char>* pNodeRet = NULL;
	if(!preorder || !inorder || nLen<=0)
		return pNodeRet;

	int nRootIndex = find(inorder, preorder[0], nLen);
	if(-1 == nRootIndex) //can't find this node, that means input got problem
		return pNodeRet;

	pNodeRet = new bin_tree_node<char>(preorder[0]);
	pNodeRet->set_lchild(
		generate_node(
						preorder+1, 
						inorder, 
						nRootIndex));
	pNodeRet->set_rchild(
		generate_node(	preorder+1+nRootIndex, 
						inorder+1+nRootIndex,
						nLen-nRootIndex-1));

	return pNodeRet;
};