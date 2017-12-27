/*
 * GameControll.h
 *
 *  Created on: 26 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_GAMECONTROL_H_
#define SERVER_INCLUDE_GAMECONTROL_H_

#include <iostream>
#include <map>
#include <string>
#include "CommandProtocol.h"
#include "Server.h"
#include "PlayMove.h"
#include "StartNewGame.h"
#include "JoinToGame.h"
#include "CloseGame.h"
#include "PrintGames.h"

using namespace std;

class GameControl {
public:
	/**
	 * constractor.
	 * @param server which will connect between clients.
	 */
    GameControl(Server* server);
    virtual void Execute(vector<string> args);
    virtual ~GameControl();
    /**
     * Start to run the server
     */
	void Run();

    void* HandleClient(void *clientArgs);

private:
    map<string, int> listGamesAndSockets;
    map<string, CommandProtocol *> commandsMap;
    Server* server;
    vector<string> gamesNameList;//optional
};

struct ClientArgs {
    int clientSocket;
    vector<pthread_t> &threadArr;
    int indexAtThreadArr;
};

#endif /* SERVER_INCLUDE_GAMECONTROL_H_ */
