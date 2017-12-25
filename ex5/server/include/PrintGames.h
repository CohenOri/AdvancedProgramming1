/*
 * PrintGames.h
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_PRINTGAMES_H_
#define SERVER_INCLUDE_PRINTGAMES_H_
#include <map>
#include "CommandProtocol.h"


class PrintGames: public CommandProtocol {
public:
	/**
	 * @param gamesMap - pointer to games map of the server.
	 */
	PrintGames(map<string, CommandProtocol *>* gamesMap);
	/**
	 * @param args- argument to whom send the game.
	 * the function sends list of names of games and its ports.
	 */
	virtual void Execute(vector<string> args);
	virtual ~PrintGames();
private:
	map<string, CommandProtocol *>* gamesMap;

};

#endif /* SERVER_INCLUDE_PRINTGAMES_H_ */
