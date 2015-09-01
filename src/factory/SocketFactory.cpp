/*
 * SocketFactory.cpp
 *
 *  Created on: Aug 11, 2015
 *      Author: Daniel Cotter
 */

#include "headers/SocketFactory.h"

void SocketFactory::generateServerSocket() {
	setupTimeout();
	setupAddress();
	createSocket();
	setupSocketOptions();
	bindSocket();
	listenOnSocket();
}

Client SocketFactory::listenForNewConnection() {
	int activity, newSocket;
	fd_set readfds;

	FD_ZERO(&readfds);
	FD_SET(actualSocket, &readfds);
	activity = select(100, &readfds, 0, 0, 0);

	if (activity < 0
			|| (newSocket = accept(actualSocket, (struct sockaddr *) &address,
					(socklen_t*) &addressLength)) < 0
			|| setsockopt(actualSocket, SOL_SOCKET, SO_RCVTIMEO,
					(char *) &timeout, sizeof(struct timeval)) < 0
			|| newSocket < 1)
		return Client(0);

	return Client(newSocket);
}

void SocketFactory::setupTimeout() {
	timeout.tv_sec = timeoutSeconds;
	timeout.tv_usec = timeoutMilliseconds;
}

void SocketFactory::setupAddress() {
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	addressLength = sizeof(address);
}

bool SocketFactory::createSocket() {
	if ((actualSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		return false;

	return true;
}

bool SocketFactory::setupSocketOptions() {
	if (setsockopt(actualSocket, SOL_SOCKET, SO_REUSEADDR, (char *) &yes,
			sizeof(yes)) < 0)
		return false;

	return true;
}

bool SocketFactory::bindSocket() {
	if (bind(actualSocket, (struct sockaddr *) &address, sizeof(address)) < 0)
		return false;

	return true;
}

bool SocketFactory::listenOnSocket() {
	if (listen(actualSocket, SOMAXCONN) < 0)
		return false;

	return true;
}

void SocketFactory::setPort(unsigned short int port) {
	this->port = port;
}

void SocketFactory::setTimeoutMilliseconds(int milliseconds) {
	timeoutMilliseconds = milliseconds;
}

void SocketFactory::setTimeoutSeconds(int seconds) {
	timeoutSeconds = seconds;
}
