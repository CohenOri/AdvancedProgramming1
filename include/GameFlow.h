/**
 * # Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */
#ifndef EX1_GAMEFLOW_H
#define EX1_GAMEFLOW_H
#include "LogicInterface.h"
#include "Board.h"
#include "EnumDeclration.h"
#include "PlayerInterface.h"

class GameFlow {
 public:
	/**
	 * Class that holds all the information in order to run the game
	 * @param logic - logic the game run with
	 * @param board - game board
	 * @param player1
	 * @param player2
	 */
  GameFlow(LogicInterface* logic, Board* board, PlayerInterface* player1, PlayerInterface* player2);
  /**
   * Run the game
   */
  void Run();
 private:
  LogicInterface* logic;
  Board* board;
  PlayerInterface* player[2];
  EnumDeclration::CellStatus currentTurn;
  /**
   * @return if Game is Over
   */
  bool GameOver();
  /**
   * prints why the game end and who is the winner
   */
  void endGame();
};

#endif //EX1_GAMEFLOW_H
