/**
 * # Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */

#include "../include/Slot.h"

using namespace std;

Slot::Slot(int row, int col) {
  this->row = row;
  this->col = col;
  this->status = EnumDeclration::E;
}

Slot::Slot(int row, int col, EnumDeclration::CellStatus status) {
  this->row = row;
  this->col = col;
  this->status = status;
}

Slot::~Slot(){
  //delete &this->status;
}


int Slot::GetRow() const {
  return row;
}

void Slot::SetRow(int row) {
  Slot::row = row;
}

int Slot::GetCol() const {
  return col;
}

void Slot::SetCol(int col) {
  Slot::col = col;
}

void Slot::Print() const {
  cout << '(' << this->GetRow() << ',' << this->GetCol() << ')' << "";
};

void Slot::PrintStatus() const {
  if (this->status == EnumDeclration::E) {
    cout << "cell status is: E" << endl;
  } else if (this->status == EnumDeclration::X) {
    cout << "cell status is: X" << endl;
  } else if (this->status == EnumDeclration::O) {
    cout << "cell status is: O" << endl;
  }
}

EnumDeclration::CellStatus Slot::GetCellStatus() const {
  return this->status;
}

bool Slot::ExistInVector(vector<Slot> v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    if (this->row == v[i].GetRow() && this->col == v[i].GetCol() && this->status == v[i].GetCellStatus()) {
      return true;
    }
  }
  return false;
}

int Slot::LocationInVector(vector<Slot> v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    if (this->row == v[i].GetRow() && this->col == v[i].GetCol() && this->status == v[i].GetCellStatus()) {
      return i;
    }
  }
  return -1;
}
Slot* Slot::CopySlot() {
  Slot* copy_of_slot = new Slot(this->GetRow(), this->GetCol(), this->GetCellStatus());
  return copy_of_slot;
}

bool Slot::operator ==(const Slot &s) const {
 return  ((this->row == s.row )&& (this->col == s.col));
}

bool Slot::operator !=(const Slot &s) const {
 return  !(*this == s);
}
