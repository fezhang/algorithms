#include "network_mock.h"

CNetworkMock::CNetworkMock():m_floodDoneNodes(0),m_dfsDoneNodes(0)
{
};

CNetworkMock::~CNetworkMock()
{
};

BOOL CNetworkMock::init(const string& fileName)
{
	FILE* pf = fopen(fileName.c_str(), "r");
	if(!pf){
		cout<<"Error! CNetworkMock::init file cannot open"<<endl;
		return FALSE;
	}
	
	int nNodes = 0;
	int nMatch = 0;
	int i = 0;
	nMatch = fscanf(pf, "%d\n", &nNodes);
	if(nMatch <= 0 || nNodes<=0){
		cout<<"Error! file format is incorrect, 1-st line should be the node count!"<<endl;
		fclose(pf);
		return FALSE;
	}

//////////////////////////////////////////////////////////////////////////
// allocate nodes
	for(i=0;i<nNodes;++i){
		string node_name("node ");
		TCHAR szTmp[10] = {0};
		itoa(i, szTmp, 10);
		node_name += szTmp;
		CNetworkNode* node = new CNetworkNode(this, node_name);
		m_nodes.push_back(node);
	}

//////////////////////////////////////////////////////////////////////////
// read neighbors 
	for(i=0;i<nNodes;++i){
		CNetworkNode* node = m_nodes[i];
		RASSERT(node);
		if(!node) continue;

		int neighbor = 0;
		fscanf(pf, "%d", &neighbor);
		while(neighbor != -1){
			// add neighbor
			RASSERT(neighbor>=0 && neighbor<nNodes);
			if(neighbor<0 || neighbor>=nNodes) //ignore
				;
			else
				node->addNeighbor(m_nodes[neighbor]);

			fscanf(pf, " %d", &neighbor);
		}
		fscanf(pf, "\n");
	}

//////////////////////////////////////////////////////////////////////////
// dump neighbors for verifying
	dump_all();

//////////////////////////////////////////////////////////////////////////
//  initialize the global random generator
	srand(0);
	int tick = GetTickCount();
	int nRound = tick%79;
	for(i=0;i<nRound;++i)
		rand();

	return TRUE;
};

void CNetworkMock::dump_all()
{
	int i, nNodes = m_nodes.size();
	for(i=0;i<nNodes;++i){
		CNetworkNode* node = m_nodes[i];
		node->DumpRelation();
	}
};

void CNetworkMock::start()
{
	int nNodes = m_nodes.size();
	for(int i=0;i<nNodes;++i){
		CNetworkNode* node = m_nodes[i];
		_beginthread(CNetworkNode::run, 0, node);
	}
};

void CNetworkMock::terminate()
{
	int nNodes = m_nodes.size();
	for(int i=0;i<nNodes;++i){
		CNetworkNode* node = m_nodes[i];
		node->getMsgQueue()->put(new CTermMsg());
	}
	
	Sleep(2000);
	cout<<"after terminate:"<<endl;
	dump_all();
};

void CNetworkMock::say_hello()
{
	int nNodes = m_nodes.size();
	for(int i=0;i<nNodes;++i){
		CNetworkNode* node = m_nodes[i];
		node->getMsgQueue()->put(new CHelloMsg());
	}
};

void CNetworkMock::flooding()
{
	CNetworkNode* one = NULL;
	if(m_nodes.size() > 0)
		one = m_nodes[0];

	if(NULL == one){
		cout<<"Error! CNetworkMock::flooding -- No any nodes."<<endl;
	}else{
		one->initFlooding();	
	}
};

void CNetworkMock::node_flood_ok(CNetworkNode* node)
{
	RASSERT(node);
	if(!node) return;
	
	cout<<"node "<<node->name()<<" flood ok."<<endl;
	
	++m_floodDoneNodes;
	if(m_floodDoneNodes == m_nodes.size()){ //flooding done, dump all
		cout<<"after flooding:"<<endl;
		dump_all();
	}
};

void CNetworkMock::node_dfs_ok(CNetworkNode* node)
{
	RASSERT(node);
	if(!node) return;

	cout<<"node "<<node->name()<<" DFS ok."<<endl;
	
	++m_dfsDoneNodes;
	if(m_dfsDoneNodes == m_nodes.size()){ //flooding done, dump all
		cout<<"after dfs:"<<endl;
		dump_all();
	}
};

void CNetworkMock::broadcast()
{
	CNetworkNode* one = NULL;
	if(m_nodes.size() > 0)
		one = m_nodes[0];
	
	if(NULL == one){
		cout<<"Error! CNetworkMock::flooding -- No any nodes."<<endl;
	}else{
		one->initBroadcast();	
	}
};

void CNetworkMock::converge()
{
	int nNodes = m_nodes.size();
	for(int i=0;i<nNodes;++i){
		CNetworkNode* node = m_nodes[i];
		if(node)
			node->initConverg();
	}
};

void CNetworkMock::dfs()
{
	int nNodes = m_nodes.size();
	for(int i=0;i<nNodes;++i){
		CNetworkNode* node = m_nodes[i];
		if(node)
			node->initForDFS();
	}
	m_nodes[0]->startDFS();
};