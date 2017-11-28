//
// Created by Ori Cohen on 29/10/2017.
//

#include "Slot.h"

using namespace std;
/**
 * Create a slot with E (Empty status)
 * @param row
 * @param col
 */
Slot::Slot(int row, int col) {
  this->row_ = row;
  this->col_ = col;
  this->status = EnumDeclration::E;
}
/**
 * Create slot with given status
 * @param row
 * @param col
 * @param status
 */
Slot::Slot(int row, int col, EnumDeclration::CellStatus status) {
  this->row_ = row;
  this->col_ = col;
  this->status = status;
}

Slot::~Slot(){
  //delete &this->status;
}

/**
 * @return row of slot
 */
int Slot::GetRow() const {
  return row_;
}
/**
 * @param row_ to set
 */
void Slot::SetRow(int row_) {
  Slot::row_ = row_;
}
/**
 * @return col of slot
 */
int Slot::GetCol() const {
  return col_;
}
/**
 * @param col_ to set
 */
void Slot::SetCol(int col_) {
  Slot::col_ = col_;
}
/**
 * Print in the (row,col) format
 */
void Slot::Print() const {
  cout << '(' << this->GetRow() << ',' << this->GetCol() << ')' << "";
};
/**
 * Prints the status of the slot (E, X, O)
 */
void Slot::PrintStatus() const {
  if (this->status == EnumDeclration::E) {
    cout << "cell status is: E" << endl;
  } else if (this->status == EnumDeclration::X) {
    cout << "cell status is: X" << endl;
  } else if (this->status == EnumDeclration::O) {
    cout << "cell status is: O" << endl;
  }
}
/**
 * @return status of the slot
 */
EnumDeclration::CellStatus Slot::GetCellStatus() const {
  return this->status;
}
/**
 * @param v vector
 * @return if the slot exist in the vector
 */
bool Slot::ExistInVector(vector<Slot> v) {
  for (int i = 0; i < v.size(); i++) {
    if (this->row_ == v[i].GetRow() && this->col_ == v[i].GetCol() && this->status == v[i].GetCellStatus()) {
      return true;
    }
  }
  return false;
}
/**
 * @param v vector
 * @return the index (location) of the slot in the given vector
 */
int Slot::LocationInVector(vector<Slot> v) {
  for (int i = 0; i < v.size(); i++) {
    if (this->row_ == v[i].GetRow() && this->col_ == v[i].GetCol() && this->status == v[i].GetCellStatus()) {
      return i;
    }
  }
  return -1;
}
Slot* Slot::CopySlot() {
  Slot* copy_of_slot = new Slot(this->GetRow(), this->GetCol(), this->GetCellStatus());
  return copy_of_slot;
}
