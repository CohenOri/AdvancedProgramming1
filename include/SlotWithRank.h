/**
 * # Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */
#ifndef ADVANCEDPROGRAMMING1_SLOTWITHRANK_H
#define ADVANCEDPROGRAMMING1_SLOTWITHRANK_H
#include "Slot.h"

class SlotWithRank {
 public:
	/**
	 * @patam Slot
	 * @param Rank-of slot.
	 */
  SlotWithRank(Slot slot, int rank);
  ~SlotWithRank();
  /**
   * @return slot.
   */
  Slot GetSlot();
  /**
   * @return rank.
   */
  int GetRank() const;
 private:
  Slot slot;
  int rank;

};

#endif //ADVANCEDPROGRAMMING1_SLOTWITHRANK_H
