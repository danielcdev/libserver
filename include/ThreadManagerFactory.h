/*
 * ThreadManagerFactory.h
 *
 *  Created on: Aug 15, 2015
 *      Author: Daniel Cotter
 */

#ifndef FACTORY_THREADMANAGERFACTORY_H_
#define FACTORY_THREADMANAGERFACTORY_H_

#include <condition_variable>
#include <exception>
#include <mutex>
#include <thread>
#include <map>
#include <unistd.h>
#include <libserver/ThreadTask.h>
#include <libserver/ThreadManager.h>
#include <libserver/Client.h>

using namespace std;

class ThreadManagerFactory: public ThreadManager {

	unsigned short int maxThreads;
	unsigned short int currentTask = 0;
	mutex threadManagerMutex;
	map<unsigned short int, condition_variable> taskNotify;
	map<unsigned short int, Client> connectionArray;
	ThreadTask *task;

	static void entryPoint(void *me, unsigned short int threadId);
	static void watcherEntryPoint(void *me);
	void threadRun(unsigned short int threadId);
	void watcherThread();

public:
	ThreadManagerFactory(unsigned short int maxThreads);
	~ThreadManagerFactory();
	void generateThreadManager();
	void newTask(Client client);
	void setTask(ThreadTask *task);
};

#endif /* FACTORY_THREADMANAGERFACTORY_H_ */
