/*
 * CloseGame.h
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_CLOSEGAME_H_
#define SERVER_INCLUDE_CLOSEGAME_H_

#include "CommandProtocol.h"
#include "CommandManager.h"

class CloseGame: public CommandProtocol {
public:
	CloseGame(CommandManager* cmdManagerPtr);
	void Execute(struct CommandInfo info);
	virtual ~CloseGame();
private:
	CommandManager* cmdManager;
};

#endif /* SERVER_INCLUDE_CLOSEGAME_H_ */
