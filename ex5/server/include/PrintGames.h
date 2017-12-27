/*
 * PrintGames.h
 *
 *  Created on: 27 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_PRINTGAMES_H_
#define SERVER_INCLUDE_PRINTGAMES_H_
#include "CommandProtocol.h"
#include <map>

class PrintGames: public CommandProtocol {
public:
	PrintGames();
	/**
	 * @param args will be list of games open.
	 * first vector is number of player's socket.
	 * send to player the list.
	 */
	 virtual void Execute(vector<string> args);
	virtual ~PrintGames();
};

#endif /* SERVER_INCLUDE_PRINTGAMES_H_ */
