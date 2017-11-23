/*
 * AiPlayer.h
 *
 *  Created on: 23 בנוב׳ 2017
 *      Author: yanap
 */

#ifndef AIPLAYER_H_
#define AIPLAYER_H_

#include "PlayerInterface.h"
#include "EnumDeclration.h"
#include "LogicInterface.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <sstream>

class AiPlayer: public PlayerInterface {
public:
	AiPlayer(EnumDeclration::CellStatus player);
	virtual ~AiPlayer();
  virtual Slot Play();
  virtual char getSymbol();
	  /**
	   * input: pointer to board and gameLogic.
	   * output:non
	   * the function make players move-depended what kind of player it is.
	   */
  virtual void makeAMove(Board* b, LogicInterface* logic_);
private:
  EnumDeclration::CellStatus player;
  char symbol;
};

#endif /* AIPLAYER_H_ */
