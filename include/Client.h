/*
 * Client.h
 *
 *  Created on: Aug 12, 2015
 *      Author: Daniel Cotter
 */

#ifndef MODEL_CLIENT_H_
#define MODEL_CLIENT_H_

#include <string>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

class Client {
protected:
	int socket = 0;

public:
	string readUntil(string delimiter);
	void send(string data);
	void close();
	Client();
	Client(int socket);
	int getSocket();

	bool compare(Client c);
	bool operator ==(Client c) {
		return compare(c);
	}
};

#endif /* MODEL_CLIENT_H_ */
