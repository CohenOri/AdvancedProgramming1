//
// Created by Ori Cohen
// ID: 207375783
//

#ifndef EX1_BOARD_H
#define EX1_BOARD_H

#include <string>
#include <vector>
#include "EnumDeclration.h"
#include "Slot.h"
using namespace std;

class Board {
 public:
  Board(unsigned long numOfRows = 8, unsigned long numOfCols = 8);
  ~Board();
  void Print() const;
  int GetCellStatus(int xLocation, int yLocation) const;
  void SetCellStatus(int xLocation, int yLocation, EnumDeclration::CellStatus status);
  int NumOfRows() const;
  int NumOfCols() const;
  vector<Slot> GetOSlots() const;
  vector<Slot> GetXSlots() const;
  vector<Slot> GetSlotsOfPlayer(EnumDeclration :: CellStatus player) const;
  void SetOSlots(vector<Slot> o_slots);
  void SetXSlots(vector<Slot> x_slots);
  bool LegalPlaceInBoard(int row, int col);
  Board* CopyBoard();
 private:
  vector<vector<int> > board_;
  vector<Slot> o_slots_;
  vector<Slot> x_slots_;
};

#endif //EX1_BOARD_H
