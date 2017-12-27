/*
 * Server.h
 *
 *  Created on: 2 בדצמ׳ 2017
 *      Author: yanap
 *      vv
 *      vv
 */

#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

#include "CheckNewClient.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

class Server {
public:
    /**
     * Constructor.
     * @param port to connect to.
     */
    Server(int port, CheckNewClient checker);

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
    void ConnectNewClients();

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
    void SendMessageToClient(int player, char *massage);

    /**
     * @param players socket number.
     * @return string massage
     * read massage from player.
     */
    char *GetMessageFromClient(int player);

    virtual ~Server();

private:
    int port;
    int serverSocket;
    CheckNewClient chkr;
    /**
     * start a game between players.
     * @param palyerX number given from server.
     * @playerY number given from server.
     */
    void handleClient(int playerX, int playerO);
};

#endif /* SRC_SERVER_SERVER_H_ */
