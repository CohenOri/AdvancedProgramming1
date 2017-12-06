/**
 * # Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */

#ifndef EX1_TERMINALPLAYER_H
#define EX1_TERMINALPLAYER_H
#include "PlayerInterface.h"
#include "EnumDeclration.h"
#include "LogicInterface.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * Define a player, player has status (X, O)
 * and play method which return a Slot
 * Terminal player actually reads the slot from terminal and converts it
 * to Slot object to return
 */
class TerminalPlayer : public PlayerInterface {
 public:
	/**
	 * @param player the side/status of the player X or O
	 */
  TerminalPlayer(EnumDeclration::CellStatus player);
  /**
   * reads from terminal "row, col" & converts it to slot
   * @return the slot the player chose to locate his tag at
   */
  Slot Play();
  char GetSymbol();
  void MakeAMove(Board *b, LogicInterface *logic);
  EnumDeclration::CellStatus getEnumSymbol();

 private:
  EnumDeclration::CellStatus player;
  char symbol;
};

#endif //EX1_TERMINALPLAYER_H
