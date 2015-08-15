#ifndef _INCLUDED_SAFE_QUEUE_H_
#define _INCLUDED_SAFE_QUEUE_H_

#include "platform.h"

//////////////////////////////////////////////////////////////////////////
// the safe queue, can be used for multi-thread

typedef void (*Clear_CallBack_Dtor)(void*);
template <typename T>
class CSafeQueue{
public:
	CSafeQueue(){};
	virtual ~CSafeQueue() {};

	void put(const T& data){  
		m_lock.Enter();
		m_queue.push(data); 
		m_lock.Leave();
	};
	/**
	 return TRUE: success, FALSE: fail
	**/
	BOOL get(T& data){
		if(empty()){
			return FALSE;
		}else{
			m_lock.Enter();

			data = m_queue.front();
			m_queue.pop();

			m_lock.Leave();
			return TRUE;
		}		
	};
	/**
	 return TRUE: success, FALSE: fail
	**/
	BOOL peak(T& data){
		if(empty()){
			return FALSE;
		}else{
			m_lock.Enter();

			data = m_queue.front();

			m_lock.Leave();
			return TRUE;
		}		
	};
	BOOL empty(){ 
	// Just read, needn't lock
		return m_queue.empty(); 
	}
	int  size() { 
	// Just read, needn't lock
		return m_queue.size(); 
	};
	/**
	 it's used for clear all elements in queue, the parameter "bNeedDelete" is used 
	 to free space for elements, bNeedDelete =
		TRUE:	call "delete obj_T"
		FALSE:	won't call "delete obj_T"
	**/
	void clear_all(Clear_CallBack_Dtor dtor = NULL)
	{
		if(!empty()){
			m_lock.Enter();
			while(!m_queue.empty())
			{
				T& data = m_queue.front();
				if(dtor){
					if(data)
						dtor((void*)data);
					else
						RASSERT(FALSE);
				}
				m_queue.pop();
			}
			m_lock.Leave();
		}
	};
private:
	CriticalSection  m_lock;	//there is a lock here
	queue<T>		 m_queue;
};

//////////////////////////////////////////////////////////////////////////
// the test func
namespace TestSafeQueue{
	inline void __test(){
		CSafeQueue<int> NQ;
		NQ.put(100);
		NQ.put(200);
		NQ.put(300);
		NQ.put(400);
		int n;
		NQ.get(n);
		cout<<" "<<n;
		NQ.get(n);
		cout<<" "<<n;
		NQ.get(n);
		cout<<" "<<n;
		NQ.get(n);
		cout<<" "<<n;
		NQ.get(n);
		
		NQ.clear_all();
	}
}

#endif //_INCLUDED_SAFE_QUEUE_H_