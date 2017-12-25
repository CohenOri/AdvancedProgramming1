/*
 * PrintGames.cpp
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#include "../include/PrintGames.h"

PrintGames::PrintGames(map<string, CommandProtocol*>* gamesMap) {
	this->gamesMap = gamesMap;
}

void PrintGames::Execute(vector<string> args) {
	//send items
}
