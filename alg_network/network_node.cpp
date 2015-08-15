#include "network_node.h"
#include "network_mock.h"

//////////////////////////////////////////////////////////////////////////
// Implementation of CNetworkNode

static void Msg_Collector(void* msg)
{
	RASSERT(msg);
	if(msg){
		delete (CMsg*)msg;
	}
};

CNetworkNode::CNetworkNode(CNetworkMock* owner, const string& name)
	:m_parent(NULL),
	m_name(name),
	m_owner(owner),
	m_convergCompleted(0)
{};

CNetworkNode::~CNetworkNode()
{
	m_myMsgQueue.clear_all(Msg_Collector);
};
	
void CNetworkNode::DumpRelation()
{
	cout<<"Neighbors of "<<name()<<":";
	itNode it = m_neighbors.begin();
	itNode itEnd = m_neighbors.end();
	for(it; it!=itEnd; ++it){
		CNetworkNode* node = *it;
		if(!node)
			RASSERT(FALSE);
		else
			cout<<" "<<node->name()<<", ";
	}
	cout<<"(parent is "<<(m_parent?(m_parent->name()):"NULL");
	cout<<",children are:";
	itEnd = m_children.end();
	for(it=m_children.begin();it!=itEnd;++it){
		CNetworkNode* node = *it;
		if(!node)
			RASSERT(FALSE);
		else
			cout<<" "<<node->name()<<", ";
	}
	cout<<")"<<endl;
};

MsgQueue* CNetworkNode::getMsgQueue()
{
	return &m_myMsgQueue;
};

void CNetworkNode::addNeighbor(CNetworkNode* node)
{
	RASSERT(node);
	if(!node) return;
	m_neighbors.push_back(node);
};

int get_sleep_time()
{
	return 50+rand()%1179;
};

void __cdecl CNetworkNode::run( void* pthis)
{
	RASSERT(pthis);
	if(!pthis){
		cout<<"CNetworkNode::run -- parameter of this pointer is NULL!"<<endl;
		return;
	}
	// before run, generator will make random generator happy
	LARGE_INTEGER pc;
	QueryPerformanceCounter(&pc);
	int i = 0;
	int tick = pc.QuadPart%157;
	for(i=0;i<tick;++i)
		rand();
	//
	CNetworkNode* node = (CNetworkNode*) pthis;
	while(TRUE){
		if(node->m_myMsgQueue.empty()){
			int ms = get_sleep_time();
			//cout<<"node "<<node->name()<<" will sleep "<<ms<<" ms"<<endl;
			Sleep(ms);
		}else{
			CMsg* msg = NULL;
			if(node->m_myMsgQueue.get(msg) && msg){
				if(MSG_TYPE_TERM == msg->GetType())
					break;	// Exit the thread
				else
					node->processMsg(msg);
				delete msg;
			}else{
				RASSERT(FALSE);
				cout<<"Error of node "<<node->name()<<"! CNetworkNode::run -- met a NULL message!"<<endl;
			}
		}
	}

	cout<<"node "<<node->name()<<" terminated!"<<endl;
};

void CNetworkNode::sendMsgTo(CMsg* msg, CNetworkNode* remote)
{
	RASSERT(msg);
	RASSERT(remote);
	if(!msg || !remote)
		return;
	
	MsgQueue* pRemoteMsgQ = remote->getMsgQueue();
	RASSERT(pRemoteMsgQ);
	if(!pRemoteMsgQ)
		return;

	pRemoteMsgQ->put(msg);
};

void CNetworkNode::processMsg(CMsg* msg)
{
	RASSERT(msg);
	if(!msg){
		cout<<"Error of node "<<name()<<"! CNetworkNode::processMsgrun -- met a NULL message!"<<endl;
		return;
	}
	switch(msg->GetType()){
	case MSG_TYPE_HELLO:
		cout<<"node "<<name()<<" say hello to you"<<endl;
		break;
	case MSG_TYPE_QUERY:
		processQueryMsg((CQueryMsg*)msg);
		break;
	case MSG_TYPE_PARENT:
		processParentMsg((CParentMsg*)msg);
		break;
	case MSG_TYPE_REJECT:
		processRejectMsg((CRejectMsg*)msg);
		break;
	case MSG_TYPE_BROADCAST:
		processBroadcastMsg((CBroadCastMsg*)msg);
		break;
	case MSG_TYPE_CONVERG:
		processConvergMsg((CConvergMsg*)msg);
		break;
	case MSG_TYPE_DFS_QUERY:
		processDFSQueryMsg((CDFSQueryMsg*)msg);
		break;
	case MSG_TYPE_DFS_PARENT:
		processDFSParentMsg((CDFSParentMsg*)msg);
		break;
	case MSG_TYPE_DFS_REJECT:
		processDFSRejectMsg((CDFSRejectMsg*)msg);
		break;
	default:
		RASSERT(FALSE);	// No implementation
		break;
	}
};

void CNetworkNode::initFlooding()
{
	itNode it = m_neighbors.begin();
	itNode itEnd = m_neighbors.end();
	for(it;it!=itEnd;++it){
		if(*it)
			sendMsgTo(new CQueryMsg(this), *it);
	}
}

void CNetworkNode::processQueryMsg(CQueryMsg* msg)
{
	RASSERT(msg);
	if(!msg) return;

	CNetworkNode* sender = msg->GetSender();
	RASSERT(sender);
	if(!sender) return;

	if(NULL == m_parent){
		m_parent = sender;
		sendMsgTo(new CParentMsg(this), sender);

// query other neighbors
		itNode it = m_neighbors.begin();
		itNode itEnd = m_neighbors.end();
		for(it;it!=itEnd;++it){
			if(*it && *it != sender)
				sendMsgTo(new CQueryMsg(this), *it);
		}
	}else{	//send reject message
		sendMsgTo(new CRejectMsg(this), sender);
	}	
};

void CNetworkNode::processParentMsg(CParentMsg* msg)
{
	RASSERT(msg);
	if(!msg) return;

	CNetworkNode* sender = msg->GetSender();
	RASSERT(sender);
	if(!sender) return;

	m_children.push_back(sender);

	int nParent = 0;
	if(m_parent) nParent = 1;
	if(nParent + m_children.size() + m_other.size() == m_neighbors.size()){
	// flooding done
		m_owner->node_flood_ok((this));
	}
};

void CNetworkNode::processRejectMsg(CRejectMsg* msg)
{
	RASSERT(msg);
	if(!msg) return;
	CNetworkNode* sender = msg->GetSender();
	RASSERT(sender);
	if(!sender) return;

	m_other.push_back(sender);

	int nParent = 0;
	if(m_parent) nParent = 1;
	if(nParent + m_children.size() + m_other.size() == m_neighbors.size()){
		// flooding done
		m_owner->node_flood_ok((this));
	}
};

void CNetworkNode::initBroadcast()
{// init from the root
	RASSERT(m_parent == NULL);
	cout<<"node "<<name()<<" initialized the broadcast algorithm."<<endl;
	itNode it = m_children.begin();
	itNode itEnd = m_children.end();
	for(it;it!=itEnd;++it){
		if(*it)
			sendMsgTo(new CBroadCastMsg(this), *it);
	}
};

void CNetworkNode::processBroadcastMsg(CBroadCastMsg* msg)
{
	RASSERT(msg);
	if(!msg) return;
	CNetworkNode* sender = msg->GetSender();
	RASSERT(sender);
	if(!sender) return;

	RASSERT(sender == m_parent);

	cout<<"node "<<name()<<" received a broadcast msg, and now forward to my children."<<endl;
	itNode it = m_children.begin();
	itNode itEnd = m_children.end();
	for(it;it!=itEnd;++it){
		if(*it)
			sendMsgTo(new CBroadCastMsg(this), *it);
	}
};

void CNetworkNode::initConverg()
{ // if leaf node, send message to parent
	if(NULL != m_parent && m_children.size() == 0){
		sendMsgTo(new CConvergMsg(this, m_convergChildren), m_parent);
	}
};

void CNetworkNode::processConvergMsg(CConvergMsg* msg)
{
	RASSERT(msg);
	if(!msg) return;
	CNetworkNode* sender = msg->GetSender();
	RASSERT(sender);
	if(!sender) return;

	m_convergChildren.append(sender->name());
	m_convergChildren.append("(");
	m_convergChildren.append(msg->getChildren());
	m_convergChildren.append(")");

	cout<<"node "<<name()<<" get the converg msg from node "<<sender->name()<<" with children "<<msg->getChildren()<<endl;
	++m_convergCompleted;

	if(m_convergCompleted == m_children.size()){
	// all children done
		if(NULL == m_parent){
		// the root
			cout<<"all children string is:"<<m_convergChildren<<endl;
		}else
			sendMsgTo(new CConvergMsg(this, m_convergChildren), m_parent);
	}
};

/////////////////////////////////////////////////////////////////////////
//
void CNetworkNode::initForDFS()
{
	m_parent = NULL;
	m_children.clear();
	itNode it = m_neighbors.begin();
	itNode itEnd = m_neighbors.end();
	for(it;it!=itEnd;++it)
		m_other.push_back(*it);
};

void CNetworkNode::startDFS()
{
	if(NULL == m_parent){
		m_parent = this;

//		itNode it, itEnd = m_other.end();
//		for(it = m_other.begin();it!=itEnd;++it){
			sendMsgTo(new CDFSQueryMsg(this), *(m_other.begin()));
			m_other.erase(m_other.begin());
//		}
//		m_other.clear();
	}
};

void CNetworkNode::processDFSQueryMsg(CDFSQueryMsg* msg)
{
	RASSERT(msg);
	if(!msg) return;
	CNetworkNode* sender = msg->GetSender();
	RASSERT(sender);
	if(!sender) return;

	if(NULL == m_parent){
		m_parent = sender;
		itNode it = find(m_other.begin(), m_other.end(), sender);
		if(it == m_other.end()){
			cout<<"Error! CNetworkNode::processDFSQueryMsg node "<<
				name()<<"can't find the parent"<<sender->name()<<endl;
		}else
			m_other.erase(it);
		
		if(!m_other.empty()){
			//itNode itEnd = m_other.end();
			//for(it = m_other.begin();it!=itEnd;++it){
				sendMsgTo(new CDFSQueryMsg(this), *(m_other.begin()));
				m_other.erase(m_other.begin());
			//}
			//m_other.clear();
		}else{
			sendMsgTo(new CDFSParentMsg(this), sender);
		}
	}else{
		sendMsgTo(new CDFSRejectMsg(this), sender);
	}
};

void CNetworkNode::processDFSParentMsg(CDFSParentMsg* msg)
{
	RASSERT(msg);
	if(!msg) return;
	CNetworkNode* sender = msg->GetSender();
	RASSERT(sender);
	if(!sender) return;

	m_children.push_back(sender);

	if(m_other.empty()){
		if(m_parent != this)
			sendMsgTo(new CDFSParentMsg(this), m_parent);

		//terminate
		m_owner->node_dfs_ok(this);
	}else{
		//itNode it, itEnd = m_other.end();
		//for(it = m_other.begin();it!=itEnd;++it){
			sendMsgTo(new CDFSQueryMsg(this), *(m_other.begin()));
			m_other.erase(m_other.begin());
		//}
		//m_other.clear();
	}
};

void CNetworkNode::processDFSRejectMsg(CDFSRejectMsg* msg)
{
	RASSERT(msg);
	if(!msg) return;
	CNetworkNode* sender = msg->GetSender();
	RASSERT(sender);
	if(!sender) return;

	if(m_other.empty()){
		if(m_parent != this)
			sendMsgTo(new CDFSParentMsg(this), m_parent);

		//terminate
		m_owner->node_dfs_ok(this);
	}else{
		//itNode it, itEnd = m_other.end();
		//for(it = m_other.begin();it!=itEnd;++it){
			sendMsgTo(new CDFSQueryMsg(this), *(m_other.begin()));
			m_other.erase(m_other.begin());
		//}
		//m_other.clear();
	}
};
