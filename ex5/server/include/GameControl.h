/*
 * GameControll.h
 *
 *  Created on: 26 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_GAMECONTROLL_H_
#define SERVER_INCLUDE_GAMECONTROLL_H_

#include <iostream>
#include <map>
#include <string>
#include "CommandProtocol.h"
#include "Server.h"
#include "CheckNewClient.h"

using namespace std;

class GameControl {
public:
    GameControl(int port);

    virtual ~GameControl();
    /**
     * Start to run the server
     */
	void Run();

    void* HandleClient(void *clientArgs);

private:
    int port;
    //int serverSocket;
    Server server;
    map<string, int> listGames;
    map<string, CommandProtocol *> commandsMap;
    CheckNewClient chkr;

};

struct ClientArgs {
    int clientSocket;
    vector<pthread_t> &threadArr;
    int indexAtThreadArr;
};

#endif /* SERVER_INCLUDE_GAMECONTROLL_H_ */
