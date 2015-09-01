/*
 * ServerSocket.h
 *
 *  Created on: Aug 16, 2015
 *      Author: Daniel Cotter
 */

#ifndef INTERFACE_SERVERSOCKET_H_
#define INTERFACE_SERVERSOCKET_H_

#include "../../model/headers/Client.h"

class ServerSocket {

public:
	virtual ~ServerSocket();
	virtual void setPort(unsigned short int port);
	virtual void setTimeoutSeconds(int seconds);
	virtual void setTimeoutMilliseconds(int milliseconds);
	virtual void generateServerSocket();
	virtual Client listenForNewConnection();
};

#endif /* INTERFACE_SERVERSOCKET_H_ */
