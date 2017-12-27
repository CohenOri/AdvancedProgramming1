/*
 * JoinToGame.h
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_JOINTOGAME_H_
#define SERVER_INCLUDE_JOINTOGAME_H_
#include "CommandProtocol.h"

class JoinToGame: public CommandProtocol {
public:
	JoinToGame();
	virtual void Execute(vector<string> args);
	virtual ~JoinToGame();
};

#endif /* SERVER_INCLUDE_JOINTOGAME_H_ */
