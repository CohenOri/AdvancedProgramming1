/**
 * # Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */
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
  /**
   * @return players symbol as char and not enum.
   */
  virtual char GetSymbol() = 0;
  /**
   * input: pointer to board and gameLogic.
   * output:non
   * the function make players move-depended what kind of player it is.
   */
  virtual void MakeAMove(Board *b, LogicInterface *logic) = 0;
  virtual EnumDeclration::CellStatus getEnumSymbol() = 0;

  virtual ~PlayerInterface() {}
};

#endif //EX1_PLAYERINTERFACE_H
