/*
 * Client.cpp
 *
 *  Created on: Aug 12, 2015
 *      Author: Daniel Cotter
 */

#include "headers/Client.h"

string Client::readUntil(string delimiter) {
	unsigned short int bytesRead = 0, length = 0, thisRead = 0;
	string buffer, finalData;
	buffer.resize(65535);

	while (1) {
		thisRead = ::read(this->socket, &buffer[0], 65534);

		if ((thisRead == 0) || (thisRead > 65534))
			break;

		bytesRead += thisRead;
		length = buffer.find(delimiter);

		if ((length > 0) && (length <= 65533)) {
			buffer.resize(bytesRead);
			finalData = buffer;
			break;
		}
	}

	return finalData;
}

void Client::send(string data) {
	::send(this->socket, data.c_str(), data.length(), MSG_NOSIGNAL);
}

void Client::close() {
	shutdown(this->socket, SHUT_RDWR);
	::close(this->socket);
}

Client::Client() {

}

Client::Client(int socket) {
	this->socket = socket;
}

int Client::getSocket() {
	return this->socket;
}

bool Client::compare(Client c) {
	return (this->socket != c.getSocket()) ? false : true;
}
