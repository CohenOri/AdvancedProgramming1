//
// Created by Ori Cohen on 12/11/2017.
//

#include "GameFlow.h"

/**
 * Class that holds all the information in order to run the game
 * @param logic - logic the game run with
 * @param board - game board
 * @param player1
 * @param player2
 */
GameFlow::GameFlow(LogicInterface *logic, Board *board, PlayerInterface *player1, PlayerInterface *player2) {
  this->logic_ = logic;
  this->board_ = board;
  this->current_turn_ = EnumDeclration::X;
  this->player[0] = player1;
  this->player[1] = player2;
  // some initialization
  board_->SetCellStatus(board_->NumOfRows()/2, board_->NumOfCols()/2, EnumDeclration::O);
  board_->SetCellStatus(board_->NumOfRows()/2+1, board_->NumOfCols()/2+1, EnumDeclration::O);
  board_->SetCellStatus(board_->NumOfRows()/2+1, board_->NumOfCols()/2, EnumDeclration::X);
  board_->SetCellStatus(board_->NumOfRows()/2, board_->NumOfCols()/2+1, EnumDeclration::X);
}
/**
 * Run the game
 */
void GameFlow::Run() {
  Board *b = this->board_;
  int tunrnConter = 0;
  b->Print();
  // run the game while it is still not over
  while (!GameOver()) {
	  //check who's turn it is.
	  if(tunrnConter%2 == 1) {
		  this->current_turn_ = EnumDeclration::O;
	  } else {
		  this->current_turn_ = EnumDeclration::X;
	  }
      // if player has possible slots to place.
   if (this->logic_->SlotsToPlace(this->current_turn_).size() != 0) {
       // player makes a move.
        this->player[tunrnConter%2]->makeAMove(this->board_, this->logic_);
   } else {
        // it doesn't have possible slots to place tag at
        // the turn passes over
    	  cout<< player[tunrnConter%2]->getSymbol() << " I'ts your move. but unfortunately you don't have anything to do," <<
             "therefore it's only fair that the play passes back to O"
             << endl;
      }
   tunrnConter++;
   this->board_->Print();//print the board.
  }
  //print end game screen.
  endGame();
}

/**
 * @return if Game is Over
 */
bool GameFlow::GameOver() {
  if (this->logic_->SlotsToPlace(EnumDeclration::X).size() != 0
      || this->logic_->SlotsToPlace(EnumDeclration::O).size() != 0) {
    return false;
  }
  return true;
}


/**
 * prints why the game end and who is the winner
 */
void GameFlow::endGame() {
	  Board *b = this->board_;

    int num_of_slots_in_board = b->NumOfRows() * b->NumOfCols();
    int num_of_used_slots = b->GetXSlots().size() + b->GetOSlots().size();
    if (num_of_used_slots >= num_of_slots_in_board) {
      cout << "Game is over, board is completely full" << endl;
    } else {
      cout << "Game is over, both sides can't make any more moves" << endl;
    }
    // declare result
    if (b->GetXSlots().size() > b->GetOSlots().size()) {
      cout << "X is the WINNER!";
    } else if (b->GetXSlots().size() < b->GetOSlots().size()) {
      cout << "O is the WINNER!";
    } else {
      cout << "It's a tie";
    }
}
