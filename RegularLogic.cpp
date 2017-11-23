//
// Created by Ori Cohen on 29/10/2017.
//

#include "RegularLogic.h"
/**
 * @param b create logic using a pointer to board
 */
RegularLogic::RegularLogic(Board *b) {
  this->b_ = b;
}
/**
 * @param cell_status tag
 * @return vector with all the slots available to place the given tag
 */
vector<Slot> RegularLogic::SlotsToPlace(EnumDeclration::CellStatus cell_status) {
  Board *b = this->b_;
  vector<Slot> overall_slots_to_place_list;
    /*
     * iterate over every X in the board, find the PossibleSlots for him
     * add it to overall slots to place list only if it doesn't in it already
     * (overall_slots_to_place_list is free of duplicates)
     */
    for (unsigned int i = 0; i < b->GetSlotsOfPlayer(cell_status).size(); i++) {
      Slot s = b->GetSlotsOfPlayer(cell_status)[i];
      vector<Slot> v = PossibleSlotsFor(s.GetCellStatus(), s.GetRow(), s.GetCol());
      for (unsigned int i = 0; i < v.size(); i++) {
        Slot slot = v[i];
        // verify that each Slot inserted only once (prevent duplicates)
        if (!slot.ExistInVector(overall_slots_to_place_list)) {
          overall_slots_to_place_list.push_back(slot);
        }
      }
    }
  return overall_slots_to_place_list;
}

/**
 * @param current_tag
 * @param row
 * @param col
 * @return vector with all the possible slots to another tag (same status) unlocked because of
 * the given tag
 */
vector<Slot> RegularLogic::PossibleSlotsFor(EnumDeclration::CellStatus current_tag, int row, int col) {
  EnumDeclration::CellStatus tags_looking_for;
  vector<Slot> possible_slots;
  if (current_tag == EnumDeclration::X) {
    tags_looking_for = EnumDeclration::O;
  } else {
    tags_looking_for = EnumDeclration::X;
  }
  /*
   * Checks if it available to place tag in each direction (there's an 8 of them)
   */
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row - 1, col - 1) && this->b_->GetCellStatus(row - 1, col - 1) == tags_looking_for) {
    // checking the slot next to it
    int row_to_check = row - 2;
    int col_to_check = col - 2;
    // check the next cell in the same direction
    RecursiveCheckNextCell(row_to_check, col_to_check, possible_slots, tags_looking_for, current_tag, MINUS, MINUS);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row - 1, col) && this->b_->GetCellStatus(row - 1, col) == tags_looking_for) {
    // checking the slot next to it
    int row_to_check = row - 2;
    int col_to_check = col;
    RecursiveCheckNextCell(row_to_check, col_to_check, possible_slots, tags_looking_for, current_tag, MINUS, NOTHING);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row - 1, col + 1) && this->b_->GetCellStatus(row - 1, col + 1) == tags_looking_for) {
    // checking the slot next to it
    int row_to_check = row - 2;
    int col_to_check = col + 2;
    RecursiveCheckNextCell(row_to_check, col_to_check, possible_slots, tags_looking_for, current_tag, MINUS, PLUS);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row, col - 1) && this->b_->GetCellStatus(row, col - 1) == tags_looking_for) {
    // checking the slot next to it
    int row_to_check = row;
    int col_to_check = col - 2;
    RecursiveCheckNextCell(row_to_check, col_to_check, possible_slots, tags_looking_for, current_tag, NOTHING, MINUS);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row, col + 1) && this->b_->GetCellStatus(row, col + 1) == tags_looking_for) {
    // checking the slot next to it
    int row_to_check = row;
    int col_to_check = col + 2;
    RecursiveCheckNextCell(row_to_check, col_to_check, possible_slots, tags_looking_for, current_tag, NOTHING, PLUS);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row + 1, col - 1) && this->b_->GetCellStatus(row + 1, col - 1) == tags_looking_for) {
    // checking the slot next to it
    int row_to_check = row + 2;
    int col_to_check = col - 2;
    RecursiveCheckNextCell(row_to_check, col_to_check, possible_slots, tags_looking_for, current_tag, PLUS, MINUS);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row + 1, col) && this->b_->GetCellStatus(row + 1, col) == tags_looking_for) {
    // checking the slot next to it
    int row_to_check = row + 2;
    int col_to_check = col;
    RecursiveCheckNextCell(row_to_check, col_to_check, possible_slots, tags_looking_for, current_tag, PLUS, NOTHING);
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row + 1, col + 1) && this->b_->GetCellStatus(row + 1, col + 1) == tags_looking_for) {
    // checking the slot next to it
    int row_to_check = row + 2;
    int col_to_check = col + 2;
    RecursiveCheckNextCell(row_to_check, col_to_check, possible_slots, tags_looking_for, current_tag, PLUS, PLUS);
  }
  return possible_slots;
}

/**
 * Return if given cell is good, bad or we have to check the also the next cell (again)
 * to place certain tag - returns a flag.
 * if the next cell filled with the tag we look for, we should check another cell (AGAIN)
 * if the next cell filled with the same tag as given tag (XOX) - nothing to do (BAD place)
 * if the next cell is empty, it is a GOOD place
 * @param row
 * @param col
 * @param current_tag
 * @param tags_looking_for
 * @return flag, cell is GOOD, BAD, or we have to check AGAIN
 */
RegularLogic::ExtraCellValidateResult RegularLogic::FlagCheckNextCell(int row,
                                                                      int col,
                                                                      EnumDeclration::CellStatus current_tag,
                                                                      EnumDeclration::CellStatus tags_looking_for) {
  // if legal place & empty - it is possible place to place the current tag
  if (this->b_->LegalPlaceInBoard(row, col) && this->b_->GetCellStatus(row, col) == EnumDeclration::E) {
    return GOOD;
  }
  // if legal place & filled with current_tag - BAD place
  if (this->b_->LegalPlaceInBoard(row, col) && this->b_->GetCellStatus(row, col) == current_tag) {
    return BAD;
  }
  // if legal place & filled with the tag we look for we have to check again the next cell
  if (this->b_->LegalPlaceInBoard(row, col) && this->b_->GetCellStatus(row, col) == tags_looking_for) {
    return AGAIN;
  }
  // default, if not legal place for example
  return BAD;
}

/**
 * Checks if a given cell is good to place tag and add it to the possible slot vector
 * @param row_to_check
 * @param col_to_check
 * @param slots_vector
 * @param tags_looking_for
 * @param current_tag
 * @param row_operation
 * @param col_operation
 */
void RegularLogic::RecursiveCheckNextCell(int row_to_check,
                                          int col_to_check,
                                          vector<Slot> &slots_vector,
                                          const EnumDeclration::CellStatus &tags_looking_for,
                                          const EnumDeclration::CellStatus &current_tag,
                                          Operation row_operation, Operation col_operation,
                                          const EnumDeclration::CellStatus &end_tag) {
  // decide whether its checking next cell to place or checks cell to flip
  ExtraCellValidateResult condition = FlagCheckNextCell(row_to_check, col_to_check, current_tag, tags_looking_for);
  if (end_tag != EnumDeclration::E) {
    condition = FlagCheckToFlipNextCell(row_to_check, col_to_check, current_tag, tags_looking_for);
  }
  switch (condition) {
    case GOOD:
      // if checks "next cell to place"
      if (end_tag == EnumDeclration::E) {
        // add to "possible slot" vector
        slots_vector.push_back(Slot(row_to_check, col_to_check));
      }
      // if checks "cells to flip", add the temp_slots_to_flip to final_slots_to_flip
      if (end_tag != EnumDeclration::E) {
        for (unsigned int k = 0; k < slots_vector.size(); k++) {
          this->final_slots_to_flip_.push_back(slots_vector[k]);
        }
      }
      break;
    case AGAIN:
      // we have to check extra cell
      // if checks "cells to flip"
      if (end_tag != EnumDeclration::E) {
        // add it "to_be_flipped" vector (don't mind the slot_vector name)
        // if the end tag is not E (end tag is the current tag...)
        slots_vector.push_back(Slot(row_to_check, col_to_check, tags_looking_for));
      }
      // optimize for the direction we check
      if (row_operation == MINUS) {
        row_to_check--;
      }
      if (row_operation == PLUS) {
        row_to_check++;
      }
      if (col_operation == MINUS) {
        col_to_check--;
      }
      if (col_operation == PLUS) {
        col_to_check++;
      }
      RecursiveCheckNextCell(row_to_check, col_to_check, slots_vector,
                             tags_looking_for, current_tag, row_operation, col_operation, end_tag);
      break;
      // default - for example BAD slot - do nothing
    default:break;
  }
}

/**
 * @param current_tag
 * @param row
 * @param col
 * @return vector with slots we have to flip because of the placement
 * of the given tag
 */
vector<Slot> RegularLogic::SlotsToFlip(EnumDeclration::CellStatus current_tag, int row, int col) {
  EnumDeclration::CellStatus tags_looking_for;
  vector<Slot> temp_slots_to_flip;
  if (current_tag == EnumDeclration::X) {
    tags_looking_for = EnumDeclration::O;
  } else {
    tags_looking_for = EnumDeclration::X;
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row - 1, col - 1) && this->b_->GetCellStatus(row - 1, col - 1) == tags_looking_for) {
    // save each slot we go trough in order to flip it later if needed
    temp_slots_to_flip.push_back(Slot(row - 1, col - 1, tags_looking_for));
    // checking the slot next to it
    int row_to_check = row - 2;
    int col_to_check = col - 2;
    RecursiveCheckNextCell(row_to_check, col_to_check, temp_slots_to_flip, tags_looking_for, current_tag, MINUS, MINUS,
                           current_tag);
    /* clear the slots we went trough from the temp vector, they already saved
     * (if needed) in the RecursiveCheck function at final_slots_to_flip_ vector member
     */
    temp_slots_to_flip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row - 1, col) && this->b_->GetCellStatus(row - 1, col) == tags_looking_for) {
    temp_slots_to_flip.push_back(Slot(row - 1, col, tags_looking_for));
    // checking the slot next to it
    int row_to_check = row - 2;
    int col_to_check = col;
    RecursiveCheckNextCell(row_to_check,
                           col_to_check,
                           temp_slots_to_flip,
                           tags_looking_for,
                           current_tag,
                           MINUS,
                           NOTHING,
                           current_tag);
    temp_slots_to_flip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row - 1, col + 1) && this->b_->GetCellStatus(row - 1, col + 1) == tags_looking_for) {
    temp_slots_to_flip.push_back(Slot(row - 1, col + 1, tags_looking_for));
    // checking the slot next to it
    int row_to_check = row - 2;
    int col_to_check = col + 2;
    RecursiveCheckNextCell(row_to_check, col_to_check, temp_slots_to_flip, tags_looking_for, current_tag, MINUS, PLUS,
                           current_tag);
    temp_slots_to_flip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row, col - 1) && this->b_->GetCellStatus(row, col - 1) == tags_looking_for) {
    temp_slots_to_flip.push_back(Slot(row, col - 1, tags_looking_for));
    // checking the slot next to it
    int row_to_check = row;
    int col_to_check = col - 2;
    RecursiveCheckNextCell(row_to_check,
                           col_to_check,
                           temp_slots_to_flip,
                           tags_looking_for,
                           current_tag,
                           NOTHING,
                           MINUS,
                           current_tag);
    temp_slots_to_flip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row, col + 1) && this->b_->GetCellStatus(row, col + 1) == tags_looking_for) {
    temp_slots_to_flip.push_back(Slot(row, col + 1, tags_looking_for));
    // checking the slot next to it
    int row_to_check = row;
    int col_to_check = col + 2;
    RecursiveCheckNextCell(row_to_check, col_to_check, temp_slots_to_flip, tags_looking_for, current_tag, NOTHING, PLUS,
                           current_tag);
    temp_slots_to_flip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row + 1, col - 1) && this->b_->GetCellStatus(row + 1, col - 1) == tags_looking_for) {
    temp_slots_to_flip.push_back(Slot(row + 1, col - 1, tags_looking_for));
    // checking the slot next to it
    int row_to_check = row + 2;
    int col_to_check = col - 2;
    RecursiveCheckNextCell(row_to_check, col_to_check, temp_slots_to_flip, tags_looking_for, current_tag, PLUS, MINUS,
                           current_tag);
    temp_slots_to_flip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row + 1, col) && this->b_->GetCellStatus(row + 1, col) == tags_looking_for) {
    temp_slots_to_flip.push_back(Slot(row + 1, col, tags_looking_for));
    // checking the slot next to it
    int row_to_check = row + 2;
    int col_to_check = col;
    RecursiveCheckNextCell(row_to_check, col_to_check, temp_slots_to_flip, tags_looking_for, current_tag, PLUS, NOTHING,
                           current_tag);
    temp_slots_to_flip.clear();
  }
  // if we find the other tag we need to check the slot next to it
  if (this->b_->LegalPlaceInBoard(row + 1, col + 1) && this->b_->GetCellStatus(row + 1, col + 1) == tags_looking_for) {
    temp_slots_to_flip.push_back(Slot(row + 1, col + 1, tags_looking_for));
    // checking the slot next to it
    int row_to_check = row + 2;
    int col_to_check = col + 2;
    RecursiveCheckNextCell(row_to_check, col_to_check, temp_slots_to_flip, tags_looking_for, current_tag, PLUS, PLUS,
                           current_tag);
    temp_slots_to_flip.clear();
  }
  return this->final_slots_to_flip_;
}

/**
 * Return if given cell is good, bad or we have to check the also the next cell (again)
 * so we have to flip all the slots between the start to end slots - returns a flag
 * "end slot is: GOOD, BAD, AGAIN" if it is indeed GOOD we have to flip slots...
 * if the next cell filled with the tag we look for, we should check another cell (AGAIN)
 * if the next cell filled with the same tag as given tag (XOX) - GOOD place
 * if the next cell is empty, it is a BAD place
 * @param row
 * @param col
 * @param current_tag
 * @param tags_looking_for
 * @return flag, cell is GOOD, BAD, or we have to check AGAIN
 */
RegularLogic::ExtraCellValidateResult RegularLogic::FlagCheckToFlipNextCell(int row,
                                                                            int col,
                                                                            EnumDeclration::CellStatus current_tag,
                                                                            EnumDeclration::CellStatus tags_looking_for) {
  // if legal place & empty - BAD place
  if (this->b_->LegalPlaceInBoard(row, col) && this->b_->GetCellStatus(row, col) == EnumDeclration::E) {
    return BAD;
  }
  // if legal place & filled with current_tag - GOOD place
  if (this->b_->LegalPlaceInBoard(row, col) && this->b_->GetCellStatus(row, col) == current_tag) {
    return GOOD;
  }
  // if legal place & filled with the tag we look for we have to check again the next cell
  if (this->b_->LegalPlaceInBoard(row, col) && this->b_->GetCellStatus(row, col) == tags_looking_for) {
    return AGAIN;
  }
  // default, if not legal place for example
  return BAD;
}
/**
 * Flips the slots which should be flipped due to the recent placement
 * of the given tag
 * @param row of the recently placed tag
 * @param col of the recently placed tag
 * @param flip_to the status of the recently placed tag
 */
void RegularLogic::FlipSlots(int row, int col, EnumDeclration::CellStatus flip_to) {
  Board *b = this->b_;
  // clear the slots to flip vector, in order to not flip an old slot unintentionally
  this->final_slots_to_flip_.clear();
  // receives all the slots we have to flip due to recent placement of the tag
  vector<Slot> slots_to_flip = SlotsToFlip(flip_to, row, col);
  EnumDeclration::CellStatus flip_from;
  if (flip_to == EnumDeclration::X) {
    flip_from = EnumDeclration::O;
  } else {
    flip_from = EnumDeclration::X;
  }
  // for each slot in slot_to_flip vector
  for (unsigned int i = 0; i < slots_to_flip.size(); i++) {
    // remove from old vector (also known as "flip_from" vector)
    if (flip_from == EnumDeclration::X) {
      // remove slots_to_flip[i] from b_->GetXSlots vector
      // if it is indeed in the vector, erase it
      int location_to_omit = slots_to_flip[i].LocationInVector(b->GetXSlots());
      vector<Slot> newXSlots;
      // if location_to_omit exist
      if (location_to_omit != -1) {
        // copy every X slot to a new vector without slot at [location to omit]
        for (unsigned int k = 0; k < b->GetXSlots().size(); k++) {
          if (k != location_to_omit) {
            newXSlots.push_back(b->GetXSlots()[k]);
          }
        }
      }
      // update the Board X slots to the new vector
      b->SetXSlots(newXSlots);
    } else {
      // the same for O slots
      int location_to_omit = slots_to_flip[i].LocationInVector(b->GetOSlots());
      vector<Slot> newOSlots;
      // if location_to_omit exist
      if (location_to_omit != -1) {
        for (unsigned int k = 0; k < b->GetOSlots().size(); k++) {
          if (k != location_to_omit) {
            newOSlots.push_back(b->GetOSlots()[k]);
          }
        }
      }
      b->SetOSlots(newOSlots);
    }
    // flip it
    b->SetCellStatus(slots_to_flip[i].GetRow(), slots_to_flip[i].GetCol(), flip_to);
  }
}
