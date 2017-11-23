//
// Created by Ori Cohen on 29/10/2017.
//

#ifndef EX1_LOGICINTERFACE_H
#define EX1_LOGICINTERFACE_H
#include "Slot.h"
#include "Board.h"
using namespace std;

class LogicInterface {
 public:
  /**
   * @return pointer to an array including all the possible slots to place tag in.
   */
  virtual vector<Slot> SlotsToPlace(EnumDeclration::CellStatus cell_status) = 0;
  /**
   * receives the row & col of the now placed tag, and the status we
   * are going to flip (if we placed X then we want to flip O)
   * @param row
   * @param col
   * @param flip_to
   */
  virtual void FlipSlots(int row, int col, EnumDeclration::CellStatus flip_to) = 0;
  virtual ~LogicInterface() {}
};

#endif //EX1_LOGICINTERFACE_H
