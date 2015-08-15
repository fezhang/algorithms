#ifndef _INCLUDED_NETWORK_MOCK_H_
#define _INCLUDED_NETWORK_MOCK_H_

#include "network_node.h"

class CNetworkMock{
public:
	typedef vector<CNetworkNode*>	arrNode;
	typedef arrNode::iterator		itNode;
public:
	CNetworkMock();
	virtual ~CNetworkMock();

	// Support init the network from a file
	BOOL init(const string& fileName);
	void start();
	void terminate();
	
	void say_hello();
	void flooding();
	void broadcast();
	void converge();
	void dfs();
	
	void node_flood_ok(CNetworkNode* node);
	void node_dfs_ok(CNetworkNode* node);
private:
	void dump_all();
private:
	arrNode		m_nodes;
	int			m_floodDoneNodes;
	int			m_dfsDoneNodes;
};

#endif //_INCLUDED_NETWORK_MOCK_H_