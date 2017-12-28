/*
 * PrintGames.h
 *
 *  Created on: 27 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_PRINTGAMES_H_
#define SERVER_INCLUDE_PRINTGAMES_H_
#include <map>

#include "CommandProtocol.h"
#include "CommandManager.h"

class PrintGames: public CommandProtocol {
public:
	PrintGames(CommandManager* cmdManagerPtr);
	/**
	 * @param args will be list of open games.
	 * first vector is number of player's socket.
	 * send to player the list.
	 */
	virtual void Execute(struct CommandInfo info);
	virtual ~PrintGames();
private:
    CommandManager* cmdManager;
};

#endif /* SERVER_INCLUDE_PRINTGAMES_H_ */
