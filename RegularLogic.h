//
// Created by Ori Cohen on 29/10/2017.
//

#ifndef EX1_REGULARLOGIC_H
#define EX1_REGULARLOGIC_H

#include "LogicInterface.h"
#include "Board.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class RegularLogic : public LogicInterface {
 public:
  RegularLogic(Board *b);
  vector<Slot> SlotsToPlace(EnumDeclration::CellStatus cell_status);
  void FlipSlots(int row, int col, EnumDeclration::CellStatus flip_to);
 private:
  /**
  * when checking another cell we get the result, bad place (can't place there tag)
  * good place, or we have to check the next cell
  */
  enum ExtraCellValidateResult {
    BAD,
    GOOD,
    AGAIN,
  };
  /**
   * recevies an operation to do to a row/col
   */
  enum Operation {
    NOTHING,
    PLUS,
    MINUS,
  };

  Board *b_;
  vector<Slot> final_slots_to_flip_;
  vector<Slot> PossibleSlotsFor(EnumDeclration::CellStatus current_tag, int row, int col);
  vector<Slot> SlotsToFlip(EnumDeclration::CellStatus current_tag, int row, int col);
  ExtraCellValidateResult FlagCheckNextCell(int row, int col, EnumDeclration::CellStatus current_tag,
                                            EnumDeclration::CellStatus tags_looking_for);

  ExtraCellValidateResult FlagCheckToFlipNextCell(int row, int col, EnumDeclration::CellStatus current_tag,
                                                  EnumDeclration::CellStatus tags_looking_for);
  void RecursiveCheckNextCell(int row_to_check,
                              int col_to_check,
                              vector<Slot> &slots_vector,
                              const EnumDeclration::CellStatus &tags_looking_for,
                              const EnumDeclration::CellStatus &current_tag,
                              Operation row_operation,
                              Operation col_operation, const EnumDeclration::CellStatus &end_tag = EnumDeclration::E);

};

#endif //EX1_REGULARLOGIC_H
