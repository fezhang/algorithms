#include "stack_use.h"

int adt_stack_usage::calc_math_expression(char* input)
{
	if(DsNULL == input)
		return INVALID_MATH_RESULT;
	
	int nInputLen = strlen(input);
	char* pPostfix = new char[nInputLen+5];
	memset(pPostfix, 0, nInputLen+5);

	if(!infix_to_postfix(input, pPostfix))
		return INVALID_MATH_RESULT;

	int nRet = calc_postfix(pPostfix);

	delete[] pPostfix;
	return nRet;
};

int adt_stack_usage::calc_postfix(char* input)
{
	if(DsNULL == input)
		return INVALID_MATH_RESULT;

	char* pInput = input;
	int nInputLen = strlen(input);
	int i = 0;

	stack_l<int> save(nInputLen);
	for(i; i<nInputLen; ++i)
	{
		switch(pInput[i])
		{
		case '+':	save.push(save.pop()+save.pop()); break;
		case '-':	save.push(save.pop()-save.pop()); break;
		case '*':	save.push(save.pop()*save.pop()); break;
		case '/':	save.push(save.pop()/save.pop()); break;
		default:
			if(pInput[i]>='0' && pInput[i]<='9')
			{
				save.push(0);
				while(pInput[i]>='0' && pInput[i]<='9')
				{
					save.push(save.pop()*10 + pInput[i]-'0');
					++i;
				}
			}
		}
	}
	int nReturn = save.pop();
	return nReturn;
};

BOOL adt_stack_usage::infix_to_postfix(char* input, char* output)
{
	if(!input || !output)
		return FALSE;
	
	int nTotalLen = strlen(input);
	int nOutPos = 0;
	stack_l<int> ops(nTotalLen);
	
	for(int i=0; i<nTotalLen; ++i)
	{
		switch(input[i])
		{
		case '(':
			ops.push(input[i]);
			break;
		case ')':	
			while(ops.top() != '(')
			{
				output[nOutPos++] = (char)ops.pop(); 
				output[nOutPos++] = ' ';
			}
			ops.pop(); //pop '('
			break;
		case '+':	
		case '-':	
			while(ops.top() == '*' || ops.top() == '/')
			{ 
				output[nOutPos++] = ops.pop(); output[nOutPos++] = ' '; 
			}
			ops.push(input[i]); 
			break;
		case '*':
		case '/':	
			ops.push(input[i]);
			break;
		default:
			if(input[i] >= '0' && input[i] <= '9')
			{
				while(input[i] >= '0' && input[i] <= '9')
				{
					output[nOutPos++] = input[i++]; 
				}
				output[nOutPos++] = ' ';
			}
			break;
		}
	}
	
	while(!ops.empty())
	{
		output[nOutPos++] = (char)ops.pop(); 
		output[nOutPos++] = ' ';
	}
	
	cout<<"	adt_stack_usage::infix_to_postfix:"<<endl;
	cout<<"		Input = "<<input<<endl;
	cout<<"		Output = "<<output<<endl;
	cout<<"	adt_stack_usage::infix_to_postfix -- END"<<endl;
	return TRUE;
};