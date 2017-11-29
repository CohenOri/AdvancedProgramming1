/**
 * # Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */

#include "../include/RegularLogic.h"

RegularLogic::RegularLogic(Board *b) {
  this->board = b;
}
vector<Slot> RegularLogic::SlotsToPlace(EnumDeclration::CellStatus cellStatus) {
  Board *b = this->board;
  vector<Slot> overallSlotsToPlaceList;
    /*
     * iterate over every X in the board, find the PossibleSlots for him
     * add it to overall slots to place list only if it doesn't in it already
     * (overallSlotsToPlaceList is free of duplicates)
     */
    for (unsigned int i = 0; i < b->GetSlotsOfPlayer(cellStatus).size(); i++) {
      Slot s = b->GetSlotsOfPlayer(cellStatus)[i];
      vector<Slot> v = PossibleSlotsFor(s.GetCellStatus(), s.GetRow(), s.GetCol());
      for (unsigned int i = 0; i < v.size(); i++) {
        Slot slot = v[i];
        // verify that each Slot inserted only once (prevent duplicates)
        if (!slot.ExistInVector(overallSlotsToPlaceList)) {
          overallSlotsToPlaceList.push_back(slot);
        }
      }
    }
  return overallSlotsToPlaceList;
}

vector<Slot> RegularLogic::PossibleSlotsFor(EnumDeclration::CellStatus currentTag, int row, int col) {
  EnumDeclration::CellStatus tagsLookingFor;
  vector<Slot> possibleSlots;
  if (currentTag == EnumDeclration::X) {
    tagsLookingFor = EnumDeclration::O;
  } else {
    tagsLookingFor = EnumDeclration::X;
  }
  /*
   * Checks if it available to place tag in each direction (there's an 8 of them)
   */
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row - 1, col - 1) &&
      this->board->GetCellStatus(row - 1, col - 1) == tagsLookingFor) {
    // checking the slot next to it
    int rowToCheck = row - 2;
    int colToCheck = col - 2;
    // check the next cell in the same direction
    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, MINUS, MINUS);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row - 1, col) &&
      this->board->GetCellStatus(row - 1, col) == tagsLookingFor) {
    // checking the slot next to it
    int rowToCheck = row - 2;
    int colToCheck = col;
    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, MINUS, NOTHING);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row - 1, col + 1) &&
      this->board->GetCellStatus(row - 1, col + 1) == tagsLookingFor) {
    // checking the slot next to it
    int rowToCheck = row - 2;
    int colToCheck = col + 2;
    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, MINUS, PLUS);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row, col - 1) && this->board->GetCellStatus(row, col - 1) == tagsLookingFor) {
    // checking the slot next to it
    int rowToCheck = row;
    int colToCheck = col - 2;
    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, NOTHING, MINUS);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row, col + 1) && this->board->GetCellStatus(row, col + 1) == tagsLookingFor) {
    // checking the slot next to it
    int rowToCheck = row;
    int colToCheck = col + 2;
    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, NOTHING, PLUS);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row + 1, col - 1) &&
      this->board->GetCellStatus(row + 1, col - 1) == tagsLookingFor) {
    // checking the slot next to it
    int rowToCheck = row + 2;
    int colToCheck = col - 2;
    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, PLUS, MINUS);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row + 1, col) && this->board->GetCellStatus(row + 1, col) == tagsLookingFor) {
    // checking the slot next to it
    int rowToCheck = row + 2;
    int colToCheck = col;
    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, PLUS, NOTHING);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row + 1, col + 1) &&
      this->board->GetCellStatus(row + 1, col + 1) == tagsLookingFor) {
    // checking the slot next to it
    int rowToCheck = row + 2;
    int colToCheck = col + 2;
    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, PLUS, PLUS);
  }
  return possibleSlots;
}


RegularLogic::ExtraCellValidateResult RegularLogic::FlagCheckNextCell(int row,
                                                                      int col,
                                                                      EnumDeclration::CellStatus currentTag,
                                                                      EnumDeclration::CellStatus tagsLookingFor) {
  // if legal place & empty - it is possible place to place the current tag
  if (this->board->LegalPlaceInBoard(row, col) && this->board->GetCellStatus(row, col) == EnumDeclration::E) {
    return GOOD;
  }
  // if legal place & filled with currentTag - BAD place
  if (this->board->LegalPlaceInBoard(row, col) && this->board->GetCellStatus(row, col) == currentTag) {
    return BAD;
  }
  // if legal place & filled with the tag we look for we have to check again the next cell
  if (this->board->LegalPlaceInBoard(row, col) && this->board->GetCellStatus(row, col) == tagsLookingFor) {
    return AGAIN;
  }
  // default, if not legal place for example
  return BAD;
}

void RegularLogic::RecursiveCheckNextCell(int rowToCheck,
                                          int colToCheck,
                                          vector<Slot> &slotsVector,
                                          const EnumDeclration::CellStatus &tagsLookingFor,
                                          const EnumDeclration::CellStatus &currentTag,
                                          Operation rowOperation, Operation colOperation,
                                          const EnumDeclration::CellStatus &endTag) {
  // decide whether its checking next cell to place or checks cell to flip
  ExtraCellValidateResult condition = FlagCheckNextCell(rowToCheck, colToCheck, currentTag, tagsLookingFor);
  if (endTag != EnumDeclration::E) {
    condition = FlagCheckToFlipNextCell(rowToCheck, colToCheck, currentTag, tagsLookingFor);
  }
  switch (condition) {
    case GOOD:
      // if checks "next cell to place"
      if (endTag == EnumDeclration::E) {
        // add to "possible slot" vector
        slotsVector.push_back(Slot(rowToCheck, colToCheck));
      }
      // if checks "cells to flip", add the tempSlotsToFlip to final_slotsToFlip
      if (endTag != EnumDeclration::E) {
        for (unsigned int k = 0; k < slotsVector.size(); k++) {
          this->finalSlotsToFlip.push_back(slotsVector[k]);
        }
      }
      break;
    case AGAIN:
      // we have to check extra cell
      // if checks "cells to flip"
      if (endTag != EnumDeclration::E) {
        // add it "to_be_flipped" vector (don't mind the slot_vector name)
        // if the end tag is not E (end tag is the current tag...)
        slotsVector.push_back(Slot(rowToCheck, colToCheck, tagsLookingFor));
      }
      // optimize for the direction we check
      if (rowOperation == MINUS) {
        rowToCheck--;
      }
      if (rowOperation == PLUS) {
        rowToCheck++;
      }
      if (colOperation == MINUS) {
        colToCheck--;
      }
      if (colOperation == PLUS) {
        colToCheck++;
      }
      RecursiveCheckNextCell(rowToCheck, colToCheck, slotsVector,
                             tagsLookingFor, currentTag, rowOperation, colOperation, endTag);
      break;
      // default - for example BAD slot - do nothing
    default:break;
  }
}

vector<Slot> RegularLogic::SlotsToFlip(EnumDeclration::CellStatus currentTag, int row, int col) {
  EnumDeclration::CellStatus tagsLookingFor;
  vector<Slot> tempSlotsToFlip;
  if (currentTag == EnumDeclration::X) {
    tagsLookingFor = EnumDeclration::O;
  } else {
    tagsLookingFor = EnumDeclration::X;
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row - 1, col - 1) &&
      this->board->GetCellStatus(row - 1, col - 1) == tagsLookingFor) {
    // save each slot we go trough in order to flip it later if needed
    tempSlotsToFlip.push_back(Slot(row - 1, col - 1, tagsLookingFor));
    // checking the slot next to it
    int rowToCheck = row - 2;
    int colToCheck = col - 2;
    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, MINUS, MINUS,
                           currentTag);
    /* clear the slots we went trough from the temp vector, they already saved
     * (if needed) in the RecursiveCheck function at finalSlotsToFlip vector member
     */
    tempSlotsToFlip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row - 1, col) && this->board->GetCellStatus(row - 1, col) == tagsLookingFor) {
    tempSlotsToFlip.push_back(Slot(row - 1, col, tagsLookingFor));
    // checking the slot next to it
    int rowToCheck = row - 2;
    int colToCheck = col;
    RecursiveCheckNextCell(rowToCheck,
                           colToCheck,
                           tempSlotsToFlip,
                           tagsLookingFor,
                           currentTag,
                           MINUS,
                           NOTHING,
                           currentTag);
    tempSlotsToFlip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row - 1, col + 1) &&
      this->board->GetCellStatus(row - 1, col + 1) == tagsLookingFor) {
    tempSlotsToFlip.push_back(Slot(row - 1, col + 1, tagsLookingFor));
    // checking the slot next to it
    int rowToCheck = row - 2;
    int colToCheck = col + 2;
    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, MINUS, PLUS,
                           currentTag);
    tempSlotsToFlip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row, col - 1) && this->board->GetCellStatus(row, col - 1) == tagsLookingFor) {
    tempSlotsToFlip.push_back(Slot(row, col - 1, tagsLookingFor));
    // checking the slot next to it
    int rowToCheck = row;
    int colToCheck = col - 2;
    RecursiveCheckNextCell(rowToCheck,
                           colToCheck,
                           tempSlotsToFlip,
                           tagsLookingFor,
                           currentTag,
                           NOTHING,
                           MINUS,
                           currentTag);
    tempSlotsToFlip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row, col + 1) && this->board->GetCellStatus(row, col + 1) == tagsLookingFor) {
    tempSlotsToFlip.push_back(Slot(row, col + 1, tagsLookingFor));
    // checking the slot next to it
    int rowToCheck = row;
    int colToCheck = col + 2;
    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, NOTHING, PLUS,
                           currentTag);
    tempSlotsToFlip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row + 1, col - 1) &&
      this->board->GetCellStatus(row + 1, col - 1) == tagsLookingFor) {
    tempSlotsToFlip.push_back(Slot(row + 1, col - 1, tagsLookingFor));
    // checking the slot next to it
    int rowToCheck = row + 2;
    int colToCheck = col - 2;
    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, PLUS, MINUS,
                           currentTag);
    tempSlotsToFlip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row + 1, col) && this->board->GetCellStatus(row + 1, col) == tagsLookingFor) {
    tempSlotsToFlip.push_back(Slot(row + 1, col, tagsLookingFor));
    // checking the slot next to it
    int rowToCheck = row + 2;
    int colToCheck = col;
    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, PLUS, NOTHING,
                           currentTag);
    tempSlotsToFlip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->board->LegalPlaceInBoard(row + 1, col + 1) &&
      this->board->GetCellStatus(row + 1, col + 1) == tagsLookingFor) {
    tempSlotsToFlip.push_back(Slot(row + 1, col + 1, tagsLookingFor));
    // checking the slot next to it
    int rowToCheck = row + 2;
    int colToCheck = col + 2;
    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, PLUS, PLUS,
                           currentTag);
    tempSlotsToFlip.clear();
  }
  return this->finalSlotsToFlip;
}


RegularLogic::ExtraCellValidateResult RegularLogic::FlagCheckToFlipNextCell(int row,
                                                                            int col,
                                                                            EnumDeclration::CellStatus currentTag,
                                                                            EnumDeclration::CellStatus tagsLookingFor) {
  // if legal place & empty - BAD place
  if (this->board->LegalPlaceInBoard(row, col) && this->board->GetCellStatus(row, col) == EnumDeclration::E) {
    return BAD;
  }
  // if legal place & filled with currentTag - GOOD place
  if (this->board->LegalPlaceInBoard(row, col) && this->board->GetCellStatus(row, col) == currentTag) {
    return GOOD;
  }
  // if legal place & filled with the tag we look for we have to check again the next cell
  if (this->board->LegalPlaceInBoard(row, col) && this->board->GetCellStatus(row, col) == tagsLookingFor) {
    return AGAIN;
  }
  // default, if not legal place for example
  return BAD;
}

void RegularLogic::FlipSlots(int row, int col, EnumDeclration::CellStatus flipTo) {
  Board *b = this->board;
  // clear the slots to flip vector, in order to not flip an old slot unintentionally
  this->finalSlotsToFlip.clear();
  // receives all the slots we have to flip due to recent placement of the tag
  vector<Slot> slotsToFlip = SlotsToFlip(flipTo, row, col);
  EnumDeclration::CellStatus flipFrom;
  if (flipTo == EnumDeclration::X) {
    flipFrom = EnumDeclration::O;
  } else {
    flipFrom = EnumDeclration::X;
  }
  // for each slot in slot_to_flip vector
  for (unsigned int i = 0; i < slotsToFlip.size(); i++) {
    // remove from old vector (also known as "flipFrom" vector)
    if (flipFrom == EnumDeclration::X) {
      // remove slotsToFlip[i] from board->GetXSlots vector
      // if it is indeed in the vector, erase it
      int locationToOmit = slotsToFlip[i].LocationInVector(b->GetXSlots());
      vector<Slot> newXSlots;
      // if locationToOmit exist
      if (locationToOmit != -1) {
        // copy every X slot to a new vector without slot at [location to omit]
        for (unsigned int k = 0; k < b->GetXSlots().size(); k++) {
          if (k != locationToOmit) {
            newXSlots.push_back(b->GetXSlots()[k]);
          }
        }
      }
      // update the Board X slots to the new vector
      b->SetXSlots(newXSlots);
    } else {
      // the same for O slots
      int locationToOmit = slotsToFlip[i].LocationInVector(b->GetOSlots());
      vector<Slot> newOSlots;
      // if locationToOmit exist
      if (locationToOmit != -1) {
        for (unsigned int k = 0; k < b->GetOSlots().size(); k++) {
          if (k != locationToOmit) {
            newOSlots.push_back(b->GetOSlots()[k]);
          }
        }
      }
      b->SetOSlots(newOSlots);
    }
    // flip it
    b->SetCellStatus(slotsToFlip[i].GetRow(), slotsToFlip[i].GetCol(), flipTo);
  }
}


LogicInterface* RegularLogic::CopyLogic(Board *b) {
  RegularLogic* copyOfRl = new RegularLogic(b);
  copyOfRl->board = b;
  return copyOfRl;
}
RegularLogic::~RegularLogic() {
}

