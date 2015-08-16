#include "adt_test.h"

void adt_testee::execute()
{
//	check_sequence();
//	calc_math_expression();
//	test_fifo_interface();
//	test_polynomial_interface();
//	test_widgets_recursive();
	test_tree_interface();
};

void adt_testee::check_sequence()
{
	DsBOOL bSequenceValid = DsFALSE;
	bSequenceValid = adt_stack_exercise::check_squence("abcde", "ecdba");
	cout<<"Sequences: abcde and ecdba are ";
	cout<<(bSequenceValid?"":"not ")<<"valid stack input and output"<<endl;

	bSequenceValid = adt_stack_exercise::check_squence("easy", "easy");
	cout<<"Sequences: easy and easy are ";
	cout<<(bSequenceValid?"":"not ")<<"valid stack input and output"<<endl;

	bSequenceValid = adt_stack_exercise::check_squence("easy", "asye");
	cout<<"Sequences: easy and asye are ";
	cout<<(bSequenceValid?"":"not ")<<"valid stack input and output"<<endl;

	bSequenceValid = adt_stack_exercise::check_squence("easy", "ayes");
	cout<<"Sequences: easy and ayes are ";
	cout<<(bSequenceValid?"":"not ")<<"valid stack input and output"<<endl;
};

void adt_testee::calc_math_expression()
{
	int nResult = 0;
	nResult = adt_stack_usage::calc_math_expression("12 * 8 + ( 9 * 3 )");
	cout<<"Result of \"12 * 8 + ( 9 * 3 ) \" is "<<nResult<<endl;

	nResult = adt_stack_usage::calc_math_expression("5 * ( ( 9 + 8 ) * 4 * 6 + 7)");
	cout<<"Result of \"5 *((9+8)*4*6+7)\" is "<<nResult<<endl;
};

void adt_testee::test_fifo_interface()
{
	adt_queue_usage::str_to_output("tryto**input*put****get***********");
	adt_queue_usage::str_to_output("what*do**you**wantho**ho***h********");
	adt_queue_usage::str_to_output("wh**at*do*g*r*yo**u*g**rg*wan**tho*g*rg*ho**gr*h**g*gr**rgr**g*rg**");
};

void adt_testee::test_polynomial_interface()
{
	cout<<"adt_testee::test_polynomial_interface -- start"<<endl;
	adt_polynomial_usage::test_ctor_dtor();
	adt_polynomial_usage::test_plus_minus();
	adt_polynomial_usage::test_multiply();
	adt_polynomial_usage::test_equal_notequal();
	adt_polynomial_usage::test_evaluate();
	cout<<"adt_testee::test_polynomial_interface -- end"<<endl;
};

void adt_testee::test_widgets_recursive()
{
	timer ter;
//	int nPos = 0;
//	int nResult = 0;
//	nResult = widgets_recursive::calc_prefix_expression("* + 7 * * 4 6 + 8 9 5", nPos);
//	cout<<"result is "<<nResult<<endl;


//	ter.Reset();
//	double dbResult = widgets_recursive::calc_log_n_factorial(1000);
//	cout<<(double)ter.Interval()<<endl;
//	cout<<"result of log(10!) is "<<dbResult<<endl;
//	
//	ter.Reset();
//	dbResult = widgets_recursive::calc_log_n_factorial(10000);
//	cout<<(double)ter.Interval()<<endl;
//	cout<<"result of log(100!) is "<<dbResult<<endl;
//	
//	ter.Reset();
//	dbResult = widgets_recursive::calc_log_n_factorial(51801);//51801
//	cout<<(double)ter.Interval()<<endl;
//	cout<<"result of log(1000!) is "<<dbResult<<endl;	

//	char chMax = widgets_recursive::get_max("hellothisismystring", 0, 19);
//	cout<<chMax<<endl;

//	chMax = widgets_recursive::get_max("whoizsyourdaddyaeroone", 0, 20);
//	cout<<chMax<<endl;

//	int nSteps = widgets_recursive::hanoitower(3);
//	cout<<"Hanoi tower, during n=3, total step is: "<<nSteps<<endl;
//
//	nSteps = widgets_recursive::hanoitower(5);
//	cout<<"Hanoi tower, during n=5, total step is: "<<nSteps<<endl;
//
//	nSteps = widgets_recursive::hanoitower(8);
//	cout<<"Hanoi tower, during n=14, total step is: "<<nSteps<<endl;
//
//	nSteps = widgets_recursive::hanoitower(16);
//	cout<<"Hanoi tower, during n=16, total step is: "<<nSteps<<endl;

	ter.Reset();
	int nFib = widgets_recursive::fibonaci(15);
	cout<<"interval = "<<(double)ter.Interval()<<endl;
	cout<<"fib(15)="<<nFib<<endl;

	ter.Reset();
	nFib = widgets_recursive::fibonaci(45);
	cout<<"interval = "<<(double)ter.Interval()<<endl;
	cout<<"fib(45)="<<nFib<<endl;

	ter.Reset();
	nFib = widgets_recursive::fibonaci(30);
	cout<<"interval = "<<(double)ter.Interval()<<endl;
	cout<<"fib(30)="<<nFib<<endl;
};

void adt_testee::test_tree_interface()
{
	tree_usage::test_tree_interface();
}