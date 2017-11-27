//
// Created by Ori Cohen on 26/11/2017.
//

#include "SlotWithRank.h"
SlotWithRank::SlotWithRank(Slot slot, int rank) : slot(slot) {
  this->slot = *new Slot(slot.GetRow(),slot.GetCol(),slot.GetCellStatus());
  this->rank = rank;
}
int SlotWithRank::GetRank() const {
  return rank;
}
Slot* SlotWithRank::GetSlot(){
  return new Slot(this->slot.GetRow(),this->slot.GetCol());
  //return &slot;
}

