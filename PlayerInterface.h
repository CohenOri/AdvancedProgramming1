//
// Created by Ori Cohen on 12/11/2017.
//

#ifndef EX1_PLAYERINTERFACE_H
#define EX1_PLAYERINTERFACE_H
#include "Slot.h"

class PlayerInterface {
 public:
  /**
   * @return the Slot the player chose to place his tag at
   */
  virtual Slot Play() = 0;
};

#endif //EX1_PLAYERINTERFACE_H
