/*
 * PlayMove.h
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SERVER_INCLUDE_PLAYMOVE_H_
#define SERVER_INCLUDE_PLAYMOVE_H_

#include "CommandProtocol.h"

class PlayMove: public CommandProtocol {
public:
	PlayMove();
	virtual void Execute(vector<string> args);
	virtual ~PlayMove();
};

#endif /* SERVER_INCLUDE_PLAYMOVE_H_ */
