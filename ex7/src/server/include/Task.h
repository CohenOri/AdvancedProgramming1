/*
 * Task.h
 *
 *  Created on: 20 בינו׳ 2018
 *      Author: yanap
 */

#ifndef INCLUDE_TASK_H_
#define INCLUDE_TASK_H_

class Task {
public:
 Task(void * (*func)(void *arg), void* arg) :
func(func), arg(arg) {}
 void execute() {
 func(arg);
 }
 virtual ~Task() {}
private:
 void * (*func)(void *arg);
 void *arg;
};

#endif /* INCLUDE_TASK_H_ */
