/*
 * StartNewGame.h
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_STARTNEWGAME_H_
#define SERVER_INCLUDE_STARTNEWGAME_H_

#include "CommandProtocol.h"

class StartNewGame: public CommandProtocol {
public:
	StartNewGame();
	virtual ~StartNewGame();
};

#endif /* SERVER_INCLUDE_STARTNEWGAME_H_ */
