/*
 * StartNewGame.h
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_STARTNEWGAME_H_
#define SERVER_INCLUDE_STARTNEWGAME_H_

#include "CommandProtocol.h"
#include "CommandManager.h"


class StartNewGame: public CommandProtocol {
public:
	StartNewGame(CommandManager* cmdManagerPtr);
	//virtual void Execute(struct CommandInfo);
    int Execute(struct CommandInfo info);
	virtual ~StartNewGame();

private:
    CommandManager* cmdManager;

};

#endif /* SERVER_INCLUDE_STARTNEWGAME_H_ */
