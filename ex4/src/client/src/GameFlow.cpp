/**
 * # Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */

#include "../include/GameFlow.h"

GameFlow::GameFlow(LogicInterface *logic, Board *board, PlayerInterface *player1, PlayerInterface *player2) {
  this->logic = logic;
  this->board = board;
  this->currentTurn = EnumDeclration::X;
  this->player[0] = player1;
  this->player[1] = player2;
  // some initialization
  board->SetCellStatus(board->NumOfRows() / 2, board->NumOfCols()/2, EnumDeclration::O);
  board->SetCellStatus(board->NumOfRows() / 2 + 1, board->NumOfCols() / 2 + 1, EnumDeclration::O);
  board->SetCellStatus(board->NumOfRows() / 2 + 1, board->NumOfCols() / 2, EnumDeclration::X);
  board->SetCellStatus(board->NumOfRows() / 2, board->NumOfCols() / 2 + 1, EnumDeclration::X);
}
void GameFlow::Run() {
  Board *b = this->board;
  int tunrnConter = 0;
  b->Print();
  // run the game while it is still not over
  while (!GameOver()) {
	  //check who's turn it is.
	  if(tunrnConter%2 == 1) {
		  this->currentTurn = EnumDeclration::O;
	  } else {
		  this->currentTurn = EnumDeclration::X;
	  }
      // if player has possible slots to place.
   if (this->logic->SlotsToPlace(this->currentTurn).size() != 0) {
       // player makes a move.
     this->player[tunrnConter % 2]->MakeAMove(this->board, this->logic);
   } else {
        // it doesn't have possible slots to place tag at
        // the turn passes over
    	  cout<< player[tunrnConter % 2]->GetSymbol()
              << " I'ts your move. but unfortunately you don't have anything to do," <<
             "therefore it's only fair that the play passes back to" <<
			 	 	 	 player[(tunrnConter + 1) % 2]->GetSymbol() << endl;
      }
   tunrnConter++;
   this->board->Print();//print the board.
  }
  //print end game screen.
  EndGame();
}

bool GameFlow::GameOver() {
  if (this->logic->SlotsToPlace(EnumDeclration::X).size() != 0
      || this->logic->SlotsToPlace(EnumDeclration::O).size() != 0) {
    return false;
  }
  return true;
}

void GameFlow::EndGame() {
	  Board *b = this->board;

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
