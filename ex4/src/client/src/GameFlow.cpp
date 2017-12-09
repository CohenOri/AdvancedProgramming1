/**
 * # Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */

#include "../include/GameFlow.h"

GameFlow::GameFlow(LogicInterface *logic, Board *board, PlayerInterface *player1, PlayerInterface *player2, bool server) {
  this->logic = logic;
  this->board = board;
  this->currentTurn = EnumDeclration::X;
  this->player[0] = player1;
  this->player[1] = player2;
  this->clentServer = server;
  // some initialization
  board->SetCellStatus(board->NumOfRows() / 2, board->NumOfCols()/2, EnumDeclration::O);
  board->SetCellStatus(board->NumOfRows() / 2 + 1, board->NumOfCols() / 2 + 1, EnumDeclration::O);
  board->SetCellStatus(board->NumOfRows() / 2 + 1, board->NumOfCols() / 2, EnumDeclration::X);
  board->SetCellStatus(board->NumOfRows() / 2, board->NumOfCols() / 2 + 1, EnumDeclration::X);
}
void GameFlow::Run() {
  Board *b = this->board;
  int tunrnConter = 0;
  // run the game while it is still not over
	b->Print();
  while (!GameOver()) {
	  //check who's turn it is.
	/*  if(tunrnConter%2 == 1) {
		  this->currentTurn = EnumDeclration::O;
	  } else {
		  this->currentTurn = EnumDeclration::X;
	  }*/
      // if player has possible slots to place.
   if (this->logic->SlotsToPlace(this->player[tunrnConter % 2]->getEnumSymbol()).size() != 0) {
       // player makes a move.
	   if(clentServer && this->player[tunrnConter % 2] == NULL) continue;
     this->player[tunrnConter % 2]->MakeAMove(this->board, this->logic);
		if(!(clentServer && tunrnConter % 2 == 0)) b->Print();
   } else {
	   //in server-client mode: we have to send lastmove and recive nomove ene if
	   //we know other player cant move.
	   if(clentServer && (tunrnConter % 2 == 0)) {
		   this->player[tunrnConter % 2]->MakeAMove(this->board, this->logic);
		   tunrnConter++;
		   continue;
	   }
        // it doesn't have possible slots to place tag at
        // the turn passes over
    	  cout<< player[tunrnConter % 2]->GetSymbol()
              << " I'ts your move. but unfortunately you don't have anything to do," <<
             "therefore it's only fair that the play passes back to " <<
			 	 	 	 player[(tunrnConter + 1) % 2]->GetSymbol() << endl;
    	  this->board->SetLastMove("NoMove");
    	  //if(clentServer) this->player[tunrnConter % 2]->MakeAMove(NULL, NULL);
      }
   tunrnConter++;
   //this->board->Print();//print the board.
  }
  //print end game screen.
  EndGame();
}

bool GameFlow::GameOver() {
  if (this->logic->SlotsToPlace(EnumDeclration::X).size() != 0
      || this->logic->SlotsToPlace(EnumDeclration::O).size() != 0) {
    return false;
  }//if its the end of board and we made last move- send to server end.
  if(this->board->GetLastMove().compare("End") != 0) {
	  if(this->clentServer) this->player[0]->MakeAMove(this->board, this->logic);
	  this->board->SetLastMove("End");
	  if(this->clentServer) this->player[0]->MakeAMove(this->board, this->logic);
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
