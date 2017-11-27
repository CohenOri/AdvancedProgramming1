//
// Created by Ori Cohen on 29/10/2017.
//

#ifndef EX1_SLOT_H
#define EX1_SLOT_H

#include <string>
#include <iostream>
#include "EnumDeclration.h"
#include <vector>
using namespace std;

/**
 * Create a slot in the format (row,col), first row/col is 1! (NOT 0)
 */
class Slot {
 public:
  Slot(int row, int col);
  Slot(int row, int col, EnumDeclration::CellStatus status);
  void Print() const;
  int GetRow() const;
  void SetRow(int row_);
  int GetCol() const;
  void SetCol(int col_);
  void PrintStatus() const;
  EnumDeclration::CellStatus GetCellStatus() const;
  bool ExistInVector(vector<Slot> v);
  int LocationInVector(vector<Slot> v);
  bool operator ==(const Slot &s) const;
  bool operator !=(const Slot &s) const;
 private:
  int row_;
  int col_;
  EnumDeclration::CellStatus status;

};

#endif //EX1_SLOT_H
