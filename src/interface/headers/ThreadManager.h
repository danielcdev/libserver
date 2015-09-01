/*
 * ThreadManager.h
 *
 *  Created on: Aug 15, 2015
 *      Author: Daniel Cotter
 */

#ifndef INTERFACE_THREADMANAGER_H_
#define INTERFACE_THREADMANAGER_H_

#include "../../interface/headers/ThreadTask.h"
#include "../../model/headers/Client.h"

class ThreadManager {

public:
	virtual ~ThreadManager();
	virtual void generateThreadManager();
	virtual void setTask(ThreadTask *task);
	virtual void newTask(Client client);
};

#endif /* INTERFACE_THREADMANAGER_H_ */
