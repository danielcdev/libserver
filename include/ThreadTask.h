/*
 * ThreadTask.h
 *
 *  Created on: Aug 12, 2015
 *      Author: Daniel Cotter
 */

#ifndef INTERFACE_THREADTASK_H_
#define INTERFACE_THREADTASK_H_

#include <libserver/Client.h>

class ThreadTask {

public:
	virtual void performTask(Client client);
	virtual ~ThreadTask();
};

#endif /* INTERFACE_THREADTASK_H_ */
