//
// Created by Ori Cohen on 12/11/2017.
//

#ifndef EX1_PLAYERINTERFACE_H
#define EX1_PLAYERINTERFACE_H
#include "Slot.h"
#include "LogicInterface.h"
#include "Board.h"

class PlayerInterface {
 public:
  /**
   * @return the Slot the player chose to place his tag at
   */
  virtual Slot Play() = 0;
  virtual char getSymbol() = 0;
  /**
   * input: pointer to board and gameLogic.
   * output:non
   * the function make players move-depended what kind of player it is.
   */
  virtual void makeAMove(Board* b, LogicInterface* logic_) = 0;
  virtual ~PlayerInterface() {}
};

#endif //EX1_PLAYERINTERFACE_H
