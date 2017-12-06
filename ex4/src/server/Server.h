/*
 * Server.h
 *
 *  Created on: 2 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX_CONNECTED_CLIENTS 10
class Server {
public:
	 Server(int port);
	 void start();
	 void stop();
	virtual ~Server();
private:
 int port;
 int serverSocket;
 void handleClient(int playerX, int playerO);
};

#endif /* SRC_SERVER_SERVER_H_ */
