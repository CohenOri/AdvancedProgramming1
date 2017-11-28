//
// Created by Ori Cohen on 26/11/2017.
//

#ifndef ADVANCEDPROGRAMMING1_SLOTWITHRANK_H
#define ADVANCEDPROGRAMMING1_SLOTWITHRANK_H
#include "Slot.h"

class SlotWithRank {
 public:
  SlotWithRank(Slot slot, int rank);
  ~SlotWithRank();
  Slot GetSlot();
  int GetRank() const;
 private:
  Slot slot;
  int rank;

};

#endif //ADVANCEDPROGRAMMING1_SLOTWITHRANK_H
