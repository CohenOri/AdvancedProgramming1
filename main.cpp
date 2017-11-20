//
// Created by Ori Cohen
// ID: 207375783
//
//changed
#include <iostream>
#include "Board.h"

#include "RegularLogic.h"
#include "GameFlow.h"
#include "TerminalPlayer.h"

using namespace std;

int main() {
  // initialize new board_, create the objects requried for
  // game flow to run and run it.
  Board* b = new Board();
  RegularLogic rl = RegularLogic(b);
  TerminalPlayer p1 = TerminalPlayer(EnumDeclration::X);
  TerminalPlayer p2 = TerminalPlayer(EnumDeclration::O);
  GameFlow gameFlow(&rl, b, &p1, &p2);
  gameFlow.Run();
  delete b;
  return 0;
}
