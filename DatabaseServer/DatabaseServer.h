#ifndef _DATABASESERVER_H_
#define _DATABASESERVER_H_

#include "ServerImpl.h"

class CDatabaseServer : public CServerImpl<CDatabaseServer>
{
public:
	CDatabaseServer(int argc, char* argv[]);
	~CDatabaseServer();
};

#endif