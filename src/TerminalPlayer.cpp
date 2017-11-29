//
/**
 * # Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */
//

#include "../include/TerminalPlayer.h"
TerminalPlayer::TerminalPlayer(EnumDeclration::CellStatus player) {
  this->player = player;
  if (player == EnumDeclration::X) {
    this->symbol = 'X';
  } else {
    this->symbol = 'O';
  }
}

Slot TerminalPlayer::Play() {
  int row;
  int col;
  int i;
  string str;
  vector<int> vect;
  cout << "\n\n" << "Please enter your row,col: ";
  getline(cin, str);
  stringstream ss(str);
  while (ss >> i) {
    vect.push_back(i);

    if (ss.peek() == ',')
      ss.ignore();
  }
  try {
    return Slot(vect.at(0), vect.at(1));
  }
  catch (exception exception) {
    cout << "Are you serious? enter something in the row, col format!";
    return Play();
  }
}

char TerminalPlayer::getSymbol() { return this->symbol; }

void TerminalPlayer::makeAMove(Board *b, LogicInterface *logic) {
  cout << this->getSymbol() << " I'ts your move.\n" << "Your possible moves: ";
  vector<Slot> v = logic->SlotsToPlace(this->player);
  for (unsigned int i = 0; i < v.size(); i++) {
    v[i].Print();
  }
  // get the chosen slot from the player, confirm its legal slot and add it to the board_.
  Slot chosen_slot = Play();
  if (chosen_slot.ExistInVector(logic->SlotsToPlace(this->player))) {
    b->SetCellStatus(chosen_slot.GetRow(), chosen_slot.GetCol(), this->player);
    logic->FlipSlots(chosen_slot.GetRow(), chosen_slot.GetCol(), this->player);
  } else {
    cout << "ILLEGAL PLACE FOR TAG " << getSymbol() << " try again" << endl;
    makeAMove(b, logic);
  }
}
