#include "console.h"
#include "network_mock.h"

int _tmain(int argc, TCHAR** argv){

	cout<<"all output are redirected to the file with name including time stamp."<<endl;
	CConsoleOutputRedirector cor(CConsoleOutputRedirector::FileName_Fixed, "output.log");
	cout<<"hello world!"<<endl;

	CNetworkMock nm;
	if(!nm.init("input.txt"))
		return 1;
	
	nm.start();

	while(TRUE){ // main thread
		TCHAR szTmp[32] = {0};
		scanf("%s", szTmp);
		if(strcmp(szTmp, "term") == 0){			//term: exit the test
			nm.terminate();
			break;
		}else if(strcmp(szTmp, "hello") == 0){	//hello: each node say hello
			nm.say_hello();
		}else if(strcmp(szTmp, "flood") == 0){	//flood: init flooding algorithm
			nm.flooding();
		}else if(strcmp(szTmp, "broad") == 0){	//broad: init broadcast algorithm
			nm.broadcast();
		}else if(strcmp(szTmp, "converg") == 0){//converg: init converg cast algorithm
			nm.converge();
		}else if(strcmp(szTmp, "dfs") == 0){	//dfs: generate the DFS tree
			nm.dfs();
		}else{									//unkown: continue read
			cout<<"Unknown command: "<<szTmp<<endl;
		}
	}

	return 0;
}