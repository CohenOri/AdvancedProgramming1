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
#include "GameControl.h"
#include "CommandProtocol.h"
#include "CommandInfo.h"
using namespace std;
#define MAX_CONNECTED_CLIENTS 10
class Server {

public:
	/**
	 * Constructor.
	 * @param port to connect to.
	 */
	 Server(int port, GameControl* controller);
	 /**
	  * start the connection.
	  */
	 void start();
	 /**
	  * stop the connection.
	  */
	 void stop();
	 /**
	  * accepts new clients.
	  */
	 int ConnectNewClients();
	 /**
	  * close connection between client and server.
	  * @param players socket number
	  */
	 void CloseClientSocket(int player);
	 /**
	  * @param players socket number
	  * @param massage string to send.
	  * send to client
	  */
	 void SendMessageToClient(int player, char* massage);
	 /**
	  * @param players socket number.
	  * @return string massage
	  * read massage from player.
	  */
	 char* GetMessageFromClient(int player);
	virtual ~Server();

private:
 int port;
 int serverSocket;
 GameControl* controller;
 map<int, pthread_t> threads;
 int stopGame;

 /**
  * start a game between players.
  * @param palyerX number given from server.
  * @playerY number given from server.
  */
 void handleClient(int playerX, int playerO);
};
struct ClientArgs {
    int clientSocket;
    int *stop;
    int serverSocket;
    map<int, pthread_t> *threadArr;
    int indexAtThreadArr;
    GameControl * controller;
};
void* HandleClient(void *clientArgs);

void* closeAllGames(void *args);

void* ServerAcceptClients(void *args);

#endif /* SRC_SERVER_SERVER_H_ */
