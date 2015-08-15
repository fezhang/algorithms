#include "datastructure_exercise.h"


BOOL adt_stack_exercise::check_squence(char* input, char* output)
{
	if(!input || !output)
	{
		cout<<"ERROR: check_squence -- NULL string as parameter"<<endl;
		return FALSE;
	}

	int nSequenceLen = strlen(input);
	if(nSequenceLen != strlen(output))
	{
		cout<<"ERROR: check_squence -- different input string len"<<endl;
		return FALSE;
	}
	
	int* arrCharIndex = new int[nSequenceLen];

	if(!arrCharIndex)
	{
		cout<<"ERROR: check_squence -- not enough memory"<<endl;
		return FALSE;
	}

	int i = 0;
	for(i=0; i<nSequenceLen; ++i)
	{
		arrCharIndex[i] = get_char_index(input, output[i]);
		if(get_char_index(input, output[i]) == -1)
		{
			cout<<"ERROR: check_squence -- wrong output string"<<endl;
			delete[] arrCharIndex;
			return FALSE;
		}
	}

	for(i=0; i<nSequenceLen; ++i)
	{
		if(arrCharIndex[i] >= 2)
		{
			int nLastIndex = -1;
			for(int j=i+1; j<nSequenceLen; ++j)
			{
				if(arrCharIndex[j] < arrCharIndex[i] && nLastIndex!=-1)
				{
					if(nLastIndex < arrCharIndex[j])
					{
						delete[] arrCharIndex;
						return FALSE;
					}
					nLastIndex = arrCharIndex[j];
				}
				else if(arrCharIndex[j] < arrCharIndex[i] && nLastIndex==-1)
					nLastIndex = arrCharIndex[j];		
			}

		}
	}
	delete[] arrCharIndex;
	return TRUE;
};

int adt_stack_exercise::get_char_index(char* str, char ch)
{
	char* pTemp = str;
	while(*pTemp != '\0')
	{
		if(*pTemp == ch)
			return pTemp-str;
		++pTemp;
	}
	return -1;	//can't find the index
};