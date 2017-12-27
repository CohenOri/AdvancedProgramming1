/*
 * PlayMove.h
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_PLAYMOVE_H_
#define SERVER_INCLUDE_PLAYMOVE_H_

#include "CommandProtocol.h"
#include "CommandManager.h"


class PlayMove: public CommandProtocol {
public:
	PlayMove(CommandManager* cmdManagerPtr);
	void Execute(struct CommandInfo info);
	virtual ~PlayMove();
private:
	CommandManager* cmdManager;
};

#endif /* SERVER_INCLUDE_PLAYMOVE_H_ */
