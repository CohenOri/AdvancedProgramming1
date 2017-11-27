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
#include "SlotWithRank.h"
#include <iostream>
#include <string>
#include <sstream>
#include <climits>

class AiPlayer : public PlayerInterface {
 public:
  AiPlayer(EnumDeclration::CellStatus player);
  AiPlayer(EnumDeclration::CellStatus player, Board * b, LogicInterface* l);

  ~AiPlayer();
  Slot Play();
  char getSymbol();
  /**
   * input: pointer to board and gameLogic.
   * output:non
   * the function make players move-depended what kind of player it is.
   */
  void makeAMove(Board *b, LogicInterface *logic_);
 private:
  EnumDeclration::CellStatus player;
  Board *board_;
  LogicInterface* logic_;
  char symbol;
};

#endif /* AIPLAYER_H_ */
