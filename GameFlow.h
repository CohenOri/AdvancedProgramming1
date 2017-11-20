//
// Created by Ori Cohen on 12/11/2017.
//changed

#ifndef EX1_GAMEFLOW_H
#define EX1_GAMEFLOW_H
#include "LogicInterface.h"
#include "Board.h"
#include "EnumDeclration.h"
#include "PlayerInterface.h"

class GameFlow {
 public:
  GameFlow(LogicInterface* logic, Board* board, PlayerInterface* player1, PlayerInterface* player2);
  void Run();
  void PlaceTag(EnumDeclration::CellStatus, bool print_board = true);
 private:
  LogicInterface* logic_;
  Board* board_;
  PlayerInterface* player1_;
  PlayerInterface* player2_;
  EnumDeclration::CellStatus current_turn_;
  bool GameOver();
  void endGame();

};

#endif //EX1_GAMEFLOW_H
