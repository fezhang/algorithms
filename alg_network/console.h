#ifndef _INCLUDED_CONSOLE_H_
#define _INCLUDED_CONSOLE_H_

#include "platform.h"  

class CConsoleOutputRedirector{
public:
	enum policy{
		FileName_With_Time = 0,
		FileName_Fixed
	};
	
	CConsoleOutputRedirector(const policy& plcy, TCHAR* fileName):m_pf(NULL)
	{
		switch(plcy) {
		case FileName_With_Time:
			{
				char fileName[256] = {0};
				get_file_name_as_time(fileName, sizeof(fileName));
				m_pf = freopen(fileName,"w",stdout);
			}
			break;
		case FileName_Fixed:
			{
				RASSERT(fileName);
				if(fileName)
					m_pf = freopen(fileName,"w",stdout);
				else
					cout<<"Error! CConsoleOutputRedirector file name is NULL!"<<endl;
			}
			break;
		default:
			RASSERT(FALSE); //at present those policies are not supported.
			break;
		}
	};
	virtual ~CConsoleOutputRedirector(){
		if(m_pf) fclose(m_pf);
	};
	
private:
	void get_file_name_as_time(char* str, int len)
	{
		RASSERT(str);
		RASSERT(len);
		if(!str || !len) return;
		
		SYSTEMTIME time;
		GetLocalTime(&time);
		
		char tmp[16]={0};
		itoa(time.wDay, tmp,10);
		strcat(str, tmp);
		strcat(str, "_");
		
		memset(tmp, 0, sizeof(tmp));
		itoa(time.wHour, tmp,10);
		strcat(str, tmp);
		strcat(str, "_");
		
		memset(tmp, 0, sizeof(tmp));
		itoa(time.wMinute, tmp,10);
		strcat(str, tmp);
		strcat(str, "_");
		
		memset(tmp, 0, sizeof(tmp));
		itoa(time.wSecond, tmp,10);
		strcat(str, tmp);
		strcat(str, ".log");
	};
	FILE*	m_pf;
};

#endif //_INCLUDED_CONSOLE_H_