#pragma once

//#include "netbase.h"
#include "google/protobuf/message.h"
#include "macro.h"
#include "IServer.h"
#include "base.h"

#include "IServerImpl.h"

class CServer : public IServer, public CErrRecord
{
public:
	CServer(IServerImpl *a_pServerImpl, event_base* a_pEventBase, SOCKET a_Socket);
	CServer(IServerImpl *a_pServerImpl, event_base *a_pEventBase, const std::string& a_strName, const std::string& a_strIP, int a_nPort, bool a_bAutoConnect = false);
	virtual ~CServer();

	//virtual void OnReadCB(const std::string& a_str);	//unfinish,a_pArg���ܻ���\0������ת��string���ضϡ�
	//virtual void OnReadCB(CSession* a_pSession, int a_nCode, void* a_pArg);
	virtual void OnReadCB(int a_nCode, void* a_pArg);
	virtual void OnWriteCB(void* a_pArg);
	virtual void OnErrorCB(void* a_pArg);

	virtual void OnPackCB(const char *a_pSource, int a_nCode, int& a_nLength, char **a_pDest);
	virtual int OnUnPackCB(const char *a_pSource, int a_nLength, int &a_nCode, char **a_pDest);
	/*
	* �ɹ���������������֮��Ļص�
	*/
	virtual bool OnConnect(CSession* a_pSession);
	/*
	*
	*/
	bool OnConnected(void* a_pArg);

	void Send(int a_nMsgCode, ::google::protobuf::Message *a_pMsg);

private:
	DEFINE_TYPE_BASE(CSession*, m_pSession, nullptr, GetSession, SetSession);
	DEFINE_TYPE_BASE(int, m_nPort, 1024, GetPort, SetPort);
	DEFINE_TYPE_REFER(std::string, m_strServerName, "", GetServerName, SetServerName);
	DEFINE_TYPE_REFER(std::string, m_strServerIP, "", GetServerIP, SetServerIP);

	IServerImpl *m_ServerImpl = nullptr;
	//DEFINE_TYPE_BASE(std::function< void(int, void*)>, m_funcMessageCB, nullptr, GetMessageCB, SetMessageCB);

	typedef void(IServerImpl::*Func)(CServer* m_pServer, int, const char *);
	Func m_funcOnMessageCB = nullptr;
};