#include "connectivity_test.h"

void connectivity_testee::execute()
{
	connectivity cty;
	uf_array ufa;
	uf_quick_tree ufqt;
	uf_weight_tree ufwt;
	uf_compression_weight_tree ufcwt;

	//cty.set_union_find_object(&ufa);
	cty.set_union_find_object(&ufqt);
	//cty.set_union_find_object(&ufwt);
	//cty.set_union_find_object(&ufcwt);

	cty.set_begin_end(0, 10000);
	cty.run();
};