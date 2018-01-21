/*
 * ThreadPool.h
 *
 *  Created on: 20 בינו׳ 2018
 *      Author: yanap
 */

#ifndef INCLUDE_THREADPOOL_H_
#define INCLUDE_THREADPOOL_H_

#include <queue>
#include <pthread.h>
#include "Task.h"
#include <iostream>
using namespace std;

class ThreadPool {

	public:
		ThreadPool(int threadsNum);
		void addTask(Task *task);
		void terminate();
		virtual ~ThreadPool();
	private:
		queue<Task *> tasksQueue;
		pthread_t* threads;
		void executeTasks();
		bool stopped;
		pthread_mutex_t lock;
		static void *execute(void *arg);
};
#endif /* INCLUDE_THREADPOOL_H_ */
