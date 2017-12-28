/*
 * JoinToGame.h
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_JOINTOGAME_H_
#define SERVER_INCLUDE_JOINTOGAME_H_

#include "CommandProtocol.h"
#include "CommandManager.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

class JoinToGame: public CommandProtocol {
public:
	JoinToGame(CommandManager* cmdManagerPtr);
	virtual void Execute(struct CommandInfo info);
	virtual ~JoinToGame();
private:
	CommandManager* cmdManager;

};

#endif /* SERVER_INCLUDE_JOINTOGAME_H_ */
