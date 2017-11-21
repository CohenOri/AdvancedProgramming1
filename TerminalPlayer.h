//
// Created by Ori Cohen on 12/11/2017.
//

#ifndef EX1_TERMINALPLAYER_H
#define EX1_TERMINALPLAYER_H
#include "PlayerInterface.h"
#include "EnumDeclration.h"
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
  TerminalPlayer(EnumDeclration::CellStatus player);
  Slot Play();
  char getSymbol();
 private:
  EnumDeclration::CellStatus player;
  char symbol;
};

#endif //EX1_TERMINALPLAYER_H
