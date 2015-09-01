/*
 * ThreadManagerFactory.cpp
 *
 *  Created on: Aug 15, 2015
 *      Author: Daniel Cotter
 */

#include "ThreadManagerFactory.h"

void ThreadManagerFactory::generateThreadManager() {
	for (unsigned short int i = 0; i <= maxThreads; i++)
		thread(ThreadManagerFactory::entryPoint, this, i).detach();

	thread(ThreadManagerFactory::watcherEntryPoint, this).detach();
}

void ThreadManagerFactory::newTask(Client client) {
	unsigned short int begin = currentTask;

	while (1) {
		if (connectionArray[currentTask].getSocket() == 0)
			break;

		(currentTask >= maxThreads) ? currentTask = 0 : currentTask++;

		if (currentTask == begin) {
			threadManagerMutex.lock();
			unsigned short int currentThreads = maxThreads;
			maxThreads = maxThreads + 10;

			for (unsigned short int i = currentThreads; i <= maxThreads; i++)
				thread(ThreadManagerFactory::entryPoint, this, i).detach();
			threadManagerMutex.unlock();
		}
	}

	threadManagerMutex.lock();
	connectionArray[currentTask] = client;
	threadManagerMutex.unlock();

	taskNotify[currentTask].notify_all();
}

void ThreadManagerFactory::entryPoint(void *me, unsigned short int threadId) {
	ThreadManagerFactory *pointer = (ThreadManagerFactory*) me;
	pointer->threadRun(threadId);
}

void ThreadManagerFactory::watcherEntryPoint(void *me) {
	ThreadManagerFactory *pointer = (ThreadManagerFactory*) me;
	pointer->watcherThread();
}

void ThreadManagerFactory::threadRun(unsigned short int threadId) {
	mutex uniqueMutex;
	while (1) {
		unique_lock < mutex > waitLock(uniqueMutex);
		taskNotify[threadId].wait(waitLock);
		waitLock.unlock();

		if (connectionArray[threadId].getSocket() == 0)
			break;

		try {
			task->performTask(connectionArray[threadId]);
		} catch (exception& e) {
			//Logging here
		}

		threadManagerMutex.lock();
		connectionArray[threadId] = Client(0);
		threadManagerMutex.unlock();
	}
}

void ThreadManagerFactory::watcherThread() {
	while (1) {
		sleep(60);

		if (maxThreads == 10)
			continue;

		threadManagerMutex.lock();
		for (unsigned short int i = maxThreads; i > 10; i--) {
			if (connectionArray[i].getSocket() != 0)
				break;

			maxThreads = maxThreads - 1;
			taskNotify[i].notify_all();
			connectionArray.erase(i);
			taskNotify.erase(i);
		}
		threadManagerMutex.unlock();
	}
}

void ThreadManagerFactory::setTask(ThreadTask *task) {
	this->task = task;
}

ThreadManagerFactory::ThreadManagerFactory(unsigned short int maxThreads) {
	this->maxThreads = (maxThreads - 1);
}

ThreadManagerFactory::~ThreadManagerFactory() {
	delete task;
}
