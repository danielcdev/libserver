/*
 * SocketFactory.h
 *
 *  Created on: Aug 11, 2015
 *      Author: Daniel Cotter
 */

#ifndef FACTORY_SOCKETFACTORY_H_
#define FACTORY_SOCKETFACTORY_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include "../../interface/headers/ServerSocket.h"
#include "../../interface/headers/ClientSocket.h"
#include "../../model/headers/Client.h"

class SocketFactory: public ServerSocket, ClientSocket {

	unsigned short int port;
	int actualSocket, timeoutSeconds = 0, timeoutMilliseconds = 0,
			addressLength = 0, yes = 1, no = 0;
	struct timeval timeout;
	struct sockaddr_in address;

	void setupTimeout();
	void setupAddress();
	bool createSocket();
	bool setupSocketOptions();
	bool bindSocket();
	bool listenOnSocket();

public:
	void generateServerSocket();
	Client listenForNewConnection();
	void setPort(unsigned short int port);
	void setTimeoutMilliseconds(int milliseconds);
	void setTimeoutSeconds(int seconds);
};

#endif /* FACTORY_SOCKETFACTORY_H_ */
