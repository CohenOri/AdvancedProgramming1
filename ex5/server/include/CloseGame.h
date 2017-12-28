/*
 * CloseGame.h
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_CLOSEGAME_H_
#define SERVER_INCLUDE_CLOSEGAME_H_

#include "CommandProtocol.h"

class CloseGame: public CommandProtocol {
public:
	CloseGame();
	virtual void Execute(vector<string> args);
	virtual ~CloseGame();
};

#endif /* SERVER_INCLUDE_CLOSEGAME_H_ */
