#include "polynomial_use.h"

void adt_polynomial_usage::test_ctor_dtor()
{
	polynomial<int> pn1;
	pn1.add_item(1,1);
	pn1.add_item(2,3);
	pn1.add_item(1,488);
	pn1.add_item(7777,7);
	pn1.add_item(-1,1);

	pn1.output();

	polynomial<int> pn2(pn1);
	pn2.output();

	polynomial<int> pn3;
	pn3.output();

	pn3 = pn1;
	pn3.output();
};

void adt_polynomial_usage::test_plus_minus()
{
	cout<<"-----------------------------------------------"<<endl;
	cout<<"-----------------------------------------------"<<endl;
	polynomial<int> pn1;
	pn1.add_item(1,1);
	pn1.add_item(2,3);
	pn1.add_item(1,488);
	pn1.add_item(7777,7);
	pn1.add_item(-1,1);

	polynomial<int> pn2;
	pn2.add_item(1,1);
	pn2.add_item(2,3);
	pn2.add_item(1,488);

	polynomial<int> pn3;
	pn3.add_item(-1,1);
	pn3.add_item(-4,3);
	pn3.add_item(1,488);

	pn1.output();
	cout<<"		+"<<endl;
	pn3.output();
	cout<<"		+"<<endl;
	pn2.output();
	cout<<"		="<<endl;

	pn1 = pn1 + pn1;
	pn1 = pn1 + pn3;
	pn1 = pn1 + pn2;
	pn1.output();
	cout<<"-----------------------------------------------"<<endl;
	cout<<"-----------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"-----------------------------------------------"<<endl;
	cout<<"-----------------------------------------------"<<endl;
	pn1.output();
	cout<<"		-"<<endl;
	pn3.output();
	cout<<"		-"<<endl;
	pn2.output();
	cout<<"		="<<endl;

	pn1 = pn1 - pn3;
	pn1 = pn1 - pn2;
	pn1.output();
	cout<<"-----------------------------------------------"<<endl;
	cout<<"-----------------------------------------------"<<endl;
};

void adt_polynomial_usage::test_multiply()
{
	polynomial<float> pn1;
	pn1.add_item(1,1);
	pn1.add_item(2,3);
	pn1.add_item(1,488);
	pn1.add_item(7777,7);
	pn1.add_item(-1,1);

	polynomial<float> pn2;
	pn2.add_item(1,1);
	pn2.add_item(2,3);

	polynomial<float> pn3;
	pn3.add_item(1,1);
	pn3.add_item(2,3);
	pn3.add_item(2,0);
	pn3.add_item(4,-1);
	pn3.add_item(3,-3);

	polynomial<float> pn4 = pn1*pn2;
	pn4.output();

	cout<<pn1.evaluate(0.5)<<"*"<<pn2.evaluate(0.5)<<"="<<pn4.evaluate(0.5)<<endl;
};

void adt_polynomial_usage::test_equal_notequal()
{
	polynomial<int> pn1;
	pn1.add_item(1,1);
	pn1.add_item(2,3);
	pn1.add_item(1,488);
	pn1.add_item(7777,7);
	pn1.add_item(-1,1);

	polynomial<int> pn2;
	pn2.add_item(1,1);
	pn2.add_item(2,3);
	pn2.add_item(1,488);

	cout<<"Polynomial 1 = ";
	pn1.output();
	cout<<"Polynomial 2 = ";
	pn2.output();
	cout<<"1 == 2?	"<<(pn1==pn2?"DsTRUE":"DsFALSE")<<endl;
	cout<<"1 != 2?	"<<(pn1!=pn2?"DsTRUE":"DsFALSE")<<endl;

	polynomial<int> pn3;
	pn3.add_item(-1,1);
	pn3.add_item(-4,3);
	pn3.add_item(1,488);
	polynomial<int> pn4(pn3);

	cout<<"Polynomial 3 = ";
	pn3.output();
	cout<<"Polynomial 4 = ";
	pn4.output();
	cout<<"3 == 4?	"<<(pn3==pn4?"DsTRUE":"DsFALSE")<<endl;
	cout<<"3 != 4?	"<<(pn3!=pn4?"DsTRUE":"DsFALSE")<<endl;
}

void adt_polynomial_usage::test_evaluate()
{
	polynomial<float> pn1;
	pn1.add_item(1,1);
	pn1.add_item(2,3);
	pn1.add_item(1,488);
	pn1.add_item(7777,7);
	pn1.add_item(-1,1);

	cout<<"Polynomial 1 = ";
	pn1.output();
	double nX = 0;
	cout<<"If X="<<nX<<" it's value = "<<pn1.evaluate(nX)<<endl;

	polynomial<float> pn2;
	pn2.add_item(1,1);
	pn2.add_item(2,3);

	cout<<"Polynomial 2 = ";
	pn2.output();
	nX = 2;
	cout<<"If X="<<nX<<" it's value = "<<pn2.evaluate(nX)<<endl;
	nX = 1;
	cout<<"If X="<<nX<<" it's value = "<<pn2.evaluate(nX)<<endl;
	nX = 2;
	cout<<"If X="<<nX<<" it's value = "<<pn2.evaluate(nX)<<endl;

	polynomial<float> pn3;
	pn3.add_item(1,1);
	pn3.add_item(2,3);
	pn3.add_item(2,0);
	pn3.add_item(4,-1);
	pn3.add_item(3,-3);

	cout<<"Polynomial 3 = ";
	pn3.output();
	nX = 2;
	cout<<"If X="<<nX<<" it's value = "<<pn3.evaluate(nX)<<endl;
	nX = 3;
	cout<<"If X="<<nX<<" it's value = "<<pn3.evaluate(nX)<<endl;
	nX = 5;
	cout<<"If X="<<nX<<" it's value = "<<pn3.evaluate(nX)<<endl;
	nX = -1;
	cout<<"If X="<<nX<<" it's value = "<<pn3.evaluate(nX)<<endl;
	nX = 1;
	cout<<"If X="<<nX<<" it's value = "<<pn3.evaluate(nX)<<endl;
};