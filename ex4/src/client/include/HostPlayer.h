/*
 * HostPlayer.h
 *
 *  Created on: 2 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SRC_CLIENT_INCLUDE_HOSTPLAYER_H_
#define SRC_CLIENT_INCLUDE_HOSTPLAYER_H_
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
using namespace std;
class HostPlayer {
public:
	HostPlayer(const char *serverIP, int serverPort);
 void connectToServer();
 int sendExercise(int arg1, char op, int arg2);
private:
 const char *serverIP;
 int serverPort;
 int clientSocket;
};

#endif /* SRC_CLIENT_INCLUDE_HOSTPLAYER_H_ */
