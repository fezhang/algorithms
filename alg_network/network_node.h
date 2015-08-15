#ifndef _INCLUDED_NETWORK_NODE_H_
#define _INCLUDED_NETWORK_NODE_H_

//////////////////////////////////////////////////////////////////////////
// Each network node has his private data

#include "safe_queue.hpp"
#include "msg.h"

class CNetworkNode;
class CNetworkMock;

typedef CSafeQueue<CMsg*>	MsgQueue;
	// to communicate with neighbors, we'd know his message queue
typedef vector<CNetworkNode*>	Neighbors;	
typedef vector<CNetworkNode*>	Children;
typedef vector<CNetworkNode*>	Other;
typedef vector<CNetworkNode*>::iterator itNode;

class CNetworkNode{
public:
	CNetworkNode(CNetworkMock* owner, const string& name);
	~CNetworkNode();
	
	void DumpRelation();
	void addNeighbor(CNetworkNode*);

	MsgQueue* getMsgQueue();
	string& name() {return m_name;};

	static void __cdecl run( void* pthis);

	void initFlooding();
	void initBroadcast();
	void initConverg();

	void initForDFS();
	void startDFS();
private:
	void processMsg(CMsg* msg);
	void sendMsgTo(CMsg* msg, CNetworkNode* remote);

//////////////////////////////////////////////////////////////////////////
// flooding algorithm to generate tree
	void processQueryMsg(CQueryMsg* msg);
	void processParentMsg(CParentMsg* msg);
	void processRejectMsg(CRejectMsg* msg);

// DFS algorithm to generate tree
	void processDFSQueryMsg(CDFSQueryMsg* msg);
	void processDFSParentMsg(CDFSParentMsg* msg);
	void processDFSRejectMsg(CDFSRejectMsg* msg);
//////////////////////////////////////////////////////////////////////////
// broadcast and convergcast
	void processBroadcastMsg(CBroadCastMsg* msg);
	void processConvergMsg(CConvergMsg* msg);
private:
	string		m_name;
	MsgQueue	m_myMsgQueue;
	Neighbors	m_neighbors;	// Physic connection with other neighbors
	CNetworkMock*	m_owner;

// Logic relation with neighbors
	CNetworkNode*	m_parent;
	Children		m_children;
	Other			m_other;

// Node status for converge algorithm
	string			m_convergChildren;
	int				m_convergCompleted;
};

#endif //_INCLUDED_NETWORK_NODE_H_