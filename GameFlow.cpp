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
  b->Print();
  // run the game while it is still not over
  while (!GameOver()) {
    if (this->current_turn_ == EnumDeclration::X) {
      // if it has possible slots to place tag at
      if (this->logic_->SlotsToPlace(EnumDeclration::X).size() != 0) {
        cout << "X I'ts your move.\n" << "Your possible moves: ";
        // prints all the possible slots & play.
        PlaceTag(EnumDeclration::X);
        // move the turn back to O, and re-check if game isn't over
        this->current_turn_ = EnumDeclration::O;
        continue;
      } else {
        // it doesn't have possible slots to place tag at
        // the turn passes over
        cout << "X I'ts your move. but unfortunately you don't have anything to do," <<
             "therefore it's only fair that the play passes back to O"
             << endl;
        // moves the turn back to O, and re-check if game isn't over
        this->current_turn_ = EnumDeclration::O;
        continue;
      }
    }
    if (this->current_turn_ == EnumDeclration::O) {
      // if it has possible slots to place tag at
      if (this->logic_->SlotsToPlace(EnumDeclration::O).size() != 0) {
        cout << "O I'ts your move.\n" << "Your possible moves: ";
        // prints all the possible slots & play.
        PlaceTag(EnumDeclration::O);
        // move the turn back to X, and re-check if game isn't over
        this->current_turn_ = EnumDeclration::X;
        continue;
      } else {
        // it doesn't have possible slots to place tag at
        // the turn passes over
        cout << "O I'ts your move. but unfortunately you don't have anything to do," <<
             "therefore it's only fair that the play passes back to X"
             << endl;
        // moves the turn back to X, and re-check if game isn't over
        this->current_turn_ = EnumDeclration::X;
        continue;
      }
    }
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
  for (int i = 0; i < v.size(); i++) {
    v[i].Print();
  }
  int row_to_place_tag_at;
  int col_to_place_tag_at;
  cout << "\n\n" << "Please enter your row,col: ";
  if (tag == EnumDeclration::X) {
    // get the chosen slot from the X player, confirm its legal slot and add it to the board_.
    Slot chosen_slot = player1_->Play();
    if (chosen_slot.ExistInVector(this->logic_->SlotsToPlace(EnumDeclration::X))) {
      this->board_->SetCellStatus(chosen_slot.GetRow(), chosen_slot.GetCol(), EnumDeclration::X);
      this->logic_->FlipSlots(chosen_slot.GetRow(), chosen_slot.GetCol(), EnumDeclration::X);
    } else {
      cout << "ILLEGAL PLACE FOR TAG X try again" << endl;
      PlaceTag(tag, false);
    }
  } else {
    // get the chosen slot from the O player, confirm its legal slot and add it to the board_.
    Slot chosen_slot = player2_->Play();
    if (chosen_slot.ExistInVector(this->logic_->SlotsToPlace(EnumDeclration::O))) {
      this->board_->SetCellStatus(chosen_slot.GetRow(), chosen_slot.GetCol(), EnumDeclration::O);
      this->logic_->FlipSlots(chosen_slot.GetRow(), chosen_slot.GetCol(), EnumDeclration::O);
    } else {
      cout << "ILLEGAL PLACE FOR TAG O try again" << endl;
      PlaceTag(tag, false);
    }
  }
  /* print the current board if it's the method wasn't recursively called (print
   * the board unless player did a bad move and we asked him to play again)
   */
  if (print_board) {
    this->board_->Print();
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
