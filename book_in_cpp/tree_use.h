#ifndef _INCLUDED_TREE_USE_H_
#define _INCLUDED_TREE_USE_H_

#include "tree.hpp"

class tree_usage
{
public:
	static void test_tree_interface();
protected:
	static void test_tree_node();
	static void test_ctor_dtor();
	
	static void test_tree_generator(); //from book: P249, E5.84
	static bin_tree<char>* generate_tree(char* preorder, char* inorder, int nLen);
	static bin_tree_node<char>* generate_node(char* preorder, char* inorder, int nLen);
};
#endif //_INCLUDED_TREE_USE_H_