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
  this->rank = rank;
}

SlotWithRank::~SlotWithRank() {
}

int SlotWithRank::GetRank() const {
  return rank;
}
Slot SlotWithRank::GetSlot(){
  return this->slot;
}


