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
  this->player1_ = player1;
  this->player2_ = player2;
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
	  if(tunrnConter%2 == 1) {
		  this->current_turn_ = EnumDeclration::O;
	  } else {
		  this->current_turn_ = EnumDeclration::X;
	  }
      // if it has possible slots to place tag at
   if (this->logic_->SlotsToPlace(this->current_turn_).size() != 0) {
        cout<< player[tunrnConter%2]->getSymbol() << " I'ts your move.\n" << "Your possible moves: ";
        // prints all the possible slots & play.
        PlaceTag(this->current_turn_);
   } else {
        // it doesn't have possible slots to place tag at
        // the turn passes over
    	  cout<< player[tunrnConter%2] << " I'ts your move. but unfortunately you don't have anything to do," <<
             "therefore it's only fair that the play passes back to O"
             << endl;
      }
   tunrnConter++;
   this->board_->Print();
  }
  //print end game screen.
  endGame();
}

/**
 * @param tag to place
 * @param print_board by default prints the board each time
 * after tag placing, it is possible to not disable this by sending false
 */
void GameFlow::PlaceTag(EnumDeclration::CellStatus tag, bool print_board) {
  // prints all the possible slots for the given tag
  vector<Slot> v = this->logic_->SlotsToPlace(tag);
  for (unsigned int i = 0; i < v.size(); i++) {
    v[i].Print();
  }
    // get the chosen slot from the player, confirm its legal slot and add it to the board_.
    Slot chosen_slot = player[tag - 1]->Play();
    if (chosen_slot.ExistInVector(this->logic_->SlotsToPlace(tag))) {
      this->board_->SetCellStatus(chosen_slot.GetRow(), chosen_slot.GetCol(), tag);
      this->logic_->FlipSlots(chosen_slot.GetRow(), chosen_slot.GetCol(), tag);
    } else {
      cout << "ILLEGAL PLACE FOR TAG "<< player[tag - 1]->getSymbol() << "try again" << endl;
      PlaceTag(tag);
    }
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
