//
/**
 * # Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */
//

#include "../include/SlotWithRank.h"
SlotWithRank::SlotWithRank(Slot slot, int rank) : slot(slot) {
  //this->slot = *new Slot(slot.GetRow(),slot.GetCol(),slot.GetCellStatus());
  this->rank = rank;
}

SlotWithRank::~SlotWithRank() {
  //delete &this->slot;
}

int SlotWithRank::GetRank() const {
  return rank;
}
Slot SlotWithRank::GetSlot(){
  return this->slot;
}


