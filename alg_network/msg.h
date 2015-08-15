#ifndef _INCLUDED_NETWORK_MSG_H_
#define _INCLUDED_NETWORK_MSG_H_

#include "platform.h"

//////////////////////////////////////////////////////////////////////////
// To simplify the implementation detail, we'll send the msg in OBJECT REF

typedef enum tagMSG_TYPE{
	MSG_TYPE_BASE = 0,
	MSG_TYPE_TERM = 1,		// to terminate the thread
	MSG_TYPE_HELLO = 2,		// say hello
//////////////////////////////////////////////////////////////////////////
//	MSGs for flooding algorithm
	MSG_TYPE_QUERY,
	MSG_TYPE_PARENT,
	MSG_TYPE_REJECT,
//	MSGs for broadcast algorithm
	MSG_TYPE_BROADCAST,
//	MSGs for converge algorithm
	MSG_TYPE_CONVERG,
//	MSGs for DFS algorithm
	MSG_TYPE_DFS_QUERY,
	MSG_TYPE_DFS_PARENT,
	MSG_TYPE_DFS_REJECT,
//////////////////////////////////////////////////////////////////////////
	MSG_TYPE_LAST			// this message will nerver be used
}MsgType;

class CNetworkNode;

class CMsg{
public:
	CMsg(MsgType tp, CNetworkNode* sender):m_type(tp),m_sender(sender){};
	virtual ~CMsg(){};

	MsgType GetType() {return m_type; };
	CNetworkNode* GetSender() { return m_sender; };
private:
	MsgType			m_type;
	CNetworkNode*	m_sender;
};

class CTermMsg: public CMsg{
public:
	CTermMsg(CNetworkNode* sender=NULL):CMsg(MSG_TYPE_TERM, sender){};
	virtual ~CTermMsg(){};
};

class CHelloMsg: public CMsg{
public:
	CHelloMsg(CNetworkNode* sender=NULL):CMsg(MSG_TYPE_HELLO, sender){};
	virtual ~CHelloMsg(){};
};

//////////////////////////////////////////////////////////////////////////
//
class CQueryMsg: public CMsg{
public:
	CQueryMsg(CNetworkNode* sender):CMsg(MSG_TYPE_QUERY, sender){};
	virtual ~CQueryMsg(){};	
};
class CParentMsg: public CMsg{
public:
	CParentMsg(CNetworkNode* sender):CMsg(MSG_TYPE_PARENT, sender){};
	virtual ~CParentMsg(){};
};
class CRejectMsg: public CMsg{
public:
	CRejectMsg(CNetworkNode* sender):CMsg(MSG_TYPE_REJECT, sender){};
	virtual ~CRejectMsg(){};
};

class CBroadCastMsg: public CMsg{
public:
	CBroadCastMsg(CNetworkNode* sender):CMsg(MSG_TYPE_BROADCAST, sender){};
	virtual ~CBroadCastMsg(){};
};
class CConvergMsg: public CMsg{
public:
	CConvergMsg(CNetworkNode* sender, const string& children)
		:CMsg(MSG_TYPE_CONVERG, sender),
		m_children(children){};

	virtual ~CConvergMsg(){};
	string& getChildren() { return m_children; };
private:
	string	m_children;
};

//////////////////////////////////////////////////////////////////
//
class CDFSQueryMsg: public CMsg{
public:
	CDFSQueryMsg(CNetworkNode* sender):CMsg(MSG_TYPE_DFS_QUERY, sender){};
	virtual ~CDFSQueryMsg(){};	
};
class CDFSParentMsg: public CMsg{
public:
	CDFSParentMsg(CNetworkNode* sender):CMsg(MSG_TYPE_DFS_PARENT, sender){};
	virtual ~CDFSParentMsg(){};
};
class CDFSRejectMsg: public CMsg{
public:
	CDFSRejectMsg(CNetworkNode* sender):CMsg(MSG_TYPE_DFS_REJECT, sender){};
	virtual ~CDFSRejectMsg(){};
};
#endif //_INCLUDED_NETWORK_MSG_H_