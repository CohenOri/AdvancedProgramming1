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
#include <sstream>
#include "CommandProtocol.h"
#include "StartNewGame.h"
#include "JoinToGame.h"
#include "PrintGames.h"

using namespace std;

class GameControl {
public:
	/**
	 * constractor.
	 * @param server which will connect between clients.
	 */
    GameControl(CommandManager* game);
    virtual ~GameControl();
    /**
     * start a command
     */
    bool executeCommand(string command, CommandInfo args);

    /**
     * stop all players and close them.
     */
	void End();
private:
    map<string, int> listGamesAndSockets;
    CommandManager* gameList;
    map<string, CommandProtocol *> commandsMap;


};


#endif /* SERVER_INCLUDE_GAMECONTROL_H_ */
