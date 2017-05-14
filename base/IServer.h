#ifndef _BASE_ISERVER_H_
#define _BASE_ISERVER_H_

#include <string>
#include <event2/event.h>
#include "macro.h"

class CSession;

class IServer
{
public:
	//IServer(event_base* a_pEventBase, CSession *a_pSession);
	IServer();
	virtual ~IServer();

	void SetCallBack();

	//virtual void OnReadCB(const std::string& a_str)  = 0;
	virtual void OnReadCB(int a_nCode, void *a_Arg) = 0;
	virtual void OnWriteCB(void* a_pArg) = 0;
	virtual void OnErrorCB(void* a_pArg) = 0;

	/*
	* ���
	*/
	virtual void OnPackCB(const char *a_pSource, int a_nCode, int& a_nLength, char **a_pDest) = 0;
	
	/*
	* ���
	*/
	virtual bool OnUnPackCB(const char *a_pSource, int a_nLength, int &a_nCode, char **a_pDest) = 0;

	virtual bool OnConnect(CSession* a_pSession) = 0;

	CSession *m_pSession = nullptr;


	//event_base* m_pEventBase = nullptr;

	//DEFINE_TYPE_BASE(CSession*, m_pSession, nullptr, GetSession, SetSession);
};

#endif