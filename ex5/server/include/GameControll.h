/*
 * GameControll.h
 *
 *  Created on: 26 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_GAMECONTROLL_H_
#define SERVER_INCLUDE_GAMECONTROLL_H_
#include <iostream>
#include <map>
#include <string>
#include "CommandProtocol.h"
using namespace std;

class GameControll {
public:
	GameControll();
	virtual ~GameControll();
private:
  map<string,int> listGames;
  map<string, CommandProtocol *> commandsMap;
};

#endif /* SERVER_INCLUDE_GAMECONTROLL_H_ */
