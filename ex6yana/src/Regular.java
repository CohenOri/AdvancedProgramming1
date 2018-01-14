import java.util.ArrayList;

public class Regular implements Logic {
private   Board board;
private	 ArrayList<Slot> finalSlotsToFlip;
	

public Regular(Board b) {
		  this.board = b;
		  this.finalSlotsToFlip = new ArrayList<Slot>(64);
		}


		public ArrayList<Slot> SlotsToPlace(CellStatus cellStatus) {
		  Board b = this.board;
		  ArrayList<Slot> overallSlotsToPlaceList = new ArrayList<Slot>(64);
		    /*
		     * iterate over every X in the board, find the PossibleSlots for him
		     * add it to overall slots to place list only if it doesn't in it already
		     * (overallSlotsToPlaceList is free of duplicates)
		     */
		    for (int i = 0; i < b.GetSlotsOfPlayer(cellStatus).size(); i++) {
		      Slot s = b.GetSlotsOfPlayer(cellStatus).get(i);
		      ArrayList<Slot> v = PossibleSlotsFor(s.GetCellStatus(), s.GetRow(), s.GetCol());
		      for ( int j = 0; j < v.size(); j++) {
		        Slot slot = v.get(j);
		        // verify that each Slot inserted only once (prevent duplicates)
		        if (!slot.ExistInArrayList(overallSlotsToPlaceList)) {
		          overallSlotsToPlaceList.add(slot);
		        }
		      }
		    }
		  return overallSlotsToPlaceList;
		}

		private ArrayList<Slot> PossibleSlotsFor(CellStatus currentTag, int row, int col) {
		  CellStatus tagsLookingFor;
		  ArrayList<Slot> possibleSlots = new ArrayList<Slot>(64);
		  if (currentTag == CellStatus.X) {
		    tagsLookingFor = CellStatus.O;
		  } else {
		    tagsLookingFor = CellStatus.X;
		  }
		  /*
		   * Checks if it available to place tag in each direction (there's an 8 of them)
		   */
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row - 1, col - 1) &&
		      this.board.GetCellStatus(row - 1, col - 1) == tagsLookingFor.ordinal()) {
		    // checking the slot next to it
		    int rowToCheck = row - 2;
		    int colToCheck = col - 2;
		    // check the next cell in the same direction
		    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, Operation.MINUS, Operation.MINUS, CellStatus.E);
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row - 1, col) &&
		      this.board.GetCellStatus(row - 1, col) == tagsLookingFor.ordinal()) {
		    // checking the slot next to it
		    int rowToCheck = row - 2;
		    int colToCheck = col;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, Operation.MINUS, Operation.NOTHING, CellStatus.E);
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row - 1, col + 1) &&
		      this.board.GetCellStatus(row - 1, col + 1) == tagsLookingFor.ordinal()) {
		    // checking the slot next to it
		    int rowToCheck = row - 2;
		    int colToCheck = col + 2;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, Operation.MINUS, Operation.PLUS, CellStatus.E);
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row, col - 1) && this.board.GetCellStatus(row, col - 1) == tagsLookingFor.ordinal()) {
		    // checking the slot next to it
		    int rowToCheck = row;
		    int colToCheck = col - 2;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, Operation.NOTHING, Operation.MINUS, CellStatus.E);
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row, col + 1) && this.board.GetCellStatus(row, col + 1) == tagsLookingFor.ordinal()) {
		    // checking the slot next to it
		    int rowToCheck = row;
		    int colToCheck = col + 2;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, Operation.NOTHING, Operation.PLUS, CellStatus.E);
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row + 1, col - 1) &&
		      this.board.GetCellStatus(row + 1, col - 1) == tagsLookingFor.ordinal()) {
		    // checking the slot next to it
		    int rowToCheck = row + 2;
		    int colToCheck = col - 2;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, Operation.PLUS, Operation.MINUS, CellStatus.E);
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row + 1, col) && this.board.GetCellStatus(row + 1, col) == tagsLookingFor.ordinal()) {
		    // checking the slot next to it
		    int rowToCheck = row + 2;
		    int colToCheck = col;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, Operation.PLUS, Operation.NOTHING, CellStatus.E);
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row + 1, col + 1) &&
		      this.board.GetCellStatus(row + 1, col + 1) == tagsLookingFor.ordinal()) {
		    // checking the slot next to it
		    int rowToCheck = row + 2;
		    int colToCheck = col + 2;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, possibleSlots, tagsLookingFor, currentTag, Operation.PLUS, Operation.PLUS, CellStatus.E);
		  }
		  return possibleSlots;
		}


		private ExtraCellValidateResult FlagCheckNextCell(int row,
		                                                                      int col,
		                                                                      CellStatus currentTag,
		                                                                      CellStatus tagsLookingFor) {
		  // if legal place & empty - it is possible place to place the current tag
		  if (this.board.LegalPlaceInBoard(row, col) && this.board.GetCellStatus(row, col) == CellStatus.E.ordinal()) {
		    return ExtraCellValidateResult.GOOD;
		  }
		  // if legal place & filled with currentTag - BAD place
		  if (this.board.LegalPlaceInBoard(row, col) && this.board.GetCellStatus(row, col) == currentTag.ordinal()) {
		    return ExtraCellValidateResult.BAD;
		  }
		  // if legal place & filled with the tag we look for we have to check again the next cell
		  if (this.board.LegalPlaceInBoard(row, col) && this.board.GetCellStatus(row, col) == tagsLookingFor.ordinal()) {
		    return ExtraCellValidateResult.AGAIN;
		  }
		  // default, if not legal place for example
		  return ExtraCellValidateResult.BAD;
		}

		private void RecursiveCheckNextCell(int rowToCheck,
		                                          int colToCheck,
		                                          ArrayList<Slot> slotsArrayList,
		                                          CellStatus tagsLookingFor,
		                                          CellStatus currentTag,
		                                          Operation rowOperation, Operation colOperation,
		                                          CellStatus endTag) {
		  // decide whether its checking next cell to place or checks cell to flip
		  ExtraCellValidateResult condition = FlagCheckNextCell(rowToCheck, colToCheck, currentTag, tagsLookingFor);
		  if (endTag != CellStatus.E) {
		    condition = FlagCheckToFlipNextCell(rowToCheck, colToCheck, currentTag, tagsLookingFor);
		  }
		  switch (condition) {
		    case GOOD:
		      // if checks "next cell to place"
		      if (endTag == CellStatus.E) {
		        // add to "possible slot" ArrayList
		        slotsArrayList.add(new Slot(rowToCheck, colToCheck));
		      }
		      // if checks "cells to flip", add the tempSlotsToFlip to final_slotsToFlip
		      if (endTag != CellStatus.E) {
		        for ( int k = 0; k < slotsArrayList.size(); k++) {
		          this.finalSlotsToFlip.add(slotsArrayList.get(k));
		        }
		      }
		      break;
		    case AGAIN:
		      // we have to check extra cell
		      // if checks "cells to flip"
		      if (endTag != CellStatus.E) {
		        // add it "to_be_flipped" ArrayList (don't mind the slot_ArrayList name)
		        // if the end tag is not E (end tag is the current tag...)
		        slotsArrayList.add(new Slot(rowToCheck, colToCheck, tagsLookingFor));
		      }
		      // optimize for the direction we check
		      if (rowOperation == Operation.MINUS) {
		        rowToCheck--;
		      }
		      if (rowOperation == Operation.PLUS) {
		        rowToCheck++;
		      }
		      if (colOperation == Operation.MINUS) {
		        colToCheck--;
		      }
		      if (colOperation == Operation.PLUS) {
		        colToCheck++;
		      }
		      RecursiveCheckNextCell(rowToCheck, colToCheck, slotsArrayList,
		                             tagsLookingFor, currentTag, rowOperation, colOperation, endTag);
		      break;
		      // default - for example BAD slot - do nothing
		    default:break;
		  }
		}

		private ArrayList<Slot> SlotsToFlip(CellStatus currentTag, int row, int col) {
		  CellStatus tagsLookingFor;
		  ArrayList<Slot> tempSlotsToFlip = new ArrayList<Slot>(64);
		  if (currentTag == CellStatus.X) {
		    tagsLookingFor = CellStatus.O;
		  } else {
		    tagsLookingFor = CellStatus.X;
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row - 1, col - 1) &&
		      this.board.GetCellStatus(row - 1, col - 1) == tagsLookingFor.ordinal()) {
		    // save each slot we go trough in order to flip it later if needed
		    tempSlotsToFlip.add(new Slot(row - 1, col - 1, tagsLookingFor));
		    // checking the slot next to it
		    int rowToCheck = row - 2;
		    int colToCheck = col - 2;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, Operation.MINUS, Operation.MINUS,
		                           currentTag);
		    /* clear the slots we went trough from the temp ArrayList, they already saved
		     * (if needed) in the RecursiveCheck function at finalSlotsToFlip ArrayList member
		     */
		    tempSlotsToFlip.clear();
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row - 1, col) && this.board.GetCellStatus(row - 1, col) == tagsLookingFor.ordinal()) {
		    tempSlotsToFlip.add(new Slot(row - 1, col, tagsLookingFor));
		    // checking the slot next to it
		    int rowToCheck = row - 2;
		    int colToCheck = col;
		    RecursiveCheckNextCell(rowToCheck,
		                           colToCheck,
		                           tempSlotsToFlip,
		                           tagsLookingFor,
		                           currentTag,
		                           Operation.MINUS,
		                           Operation.NOTHING,
		                           currentTag);
		    tempSlotsToFlip.clear();
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row - 1, col + 1) &&
		      this.board.GetCellStatus(row - 1, col + 1) == tagsLookingFor.ordinal()) {
		    tempSlotsToFlip.add(new Slot(row - 1, col + 1, tagsLookingFor));
		    // checking the slot next to it
		    int rowToCheck = row - 2;
		    int colToCheck = col + 2;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, Operation.MINUS, Operation.PLUS,
		                           currentTag);
		    tempSlotsToFlip.clear();
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row, col - 1) && this.board.GetCellStatus(row, col - 1) == tagsLookingFor.ordinal()) {
		    tempSlotsToFlip.add(new Slot(row, col - 1, tagsLookingFor));
		    // checking the slot next to it
		    int rowToCheck = row;
		    int colToCheck = col - 2;
		    RecursiveCheckNextCell(rowToCheck,
		                           colToCheck,
		                           tempSlotsToFlip,
		                           tagsLookingFor,
		                           currentTag,
		                           Operation.NOTHING,
		                           Operation.MINUS,
		                           currentTag);
		    tempSlotsToFlip.clear();
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row, col + 1) && this.board.GetCellStatus(row, col + 1) == tagsLookingFor.ordinal()) {
		    tempSlotsToFlip.add(new Slot(row, col + 1, tagsLookingFor));
		    // checking the slot next to it
		    int rowToCheck = row;
		    int colToCheck = col + 2;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, Operation.NOTHING, Operation.PLUS,
		                           currentTag);
		    tempSlotsToFlip.clear();
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row + 1, col - 1) &&
		      this.board.GetCellStatus(row + 1, col - 1) == tagsLookingFor.ordinal()) {
		    tempSlotsToFlip.add(new Slot(row + 1, col - 1, tagsLookingFor));
		    // checking the slot next to it
		    int rowToCheck = row + 2;
		    int colToCheck = col - 2;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, Operation.PLUS, Operation.MINUS,
		                           currentTag);
		    tempSlotsToFlip.clear();
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row + 1, col) && this.board.GetCellStatus(row + 1, col) == tagsLookingFor.ordinal()) {
		    tempSlotsToFlip.add(new Slot(row + 1, col, tagsLookingFor));
		    // checking the slot next to it
		    int rowToCheck = row + 2;
		    int colToCheck = col;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, Operation.PLUS, Operation.NOTHING,
		                           currentTag);
		    tempSlotsToFlip.clear();
		  }
		  // if we find the other tag we need to check the slot next to it
		  if (this.board.LegalPlaceInBoard(row + 1, col + 1) &&
		      this.board.GetCellStatus(row + 1, col + 1) == tagsLookingFor.ordinal()) {
		    tempSlotsToFlip.add(new Slot(row + 1, col + 1, tagsLookingFor));
		    // checking the slot next to it
		    int rowToCheck = row + 2;
		    int colToCheck = col + 2;
		    RecursiveCheckNextCell(rowToCheck, colToCheck, tempSlotsToFlip, tagsLookingFor, currentTag, Operation.PLUS, Operation.PLUS,
		                           currentTag);
		    tempSlotsToFlip.clear();
		  }
		  return this.finalSlotsToFlip;
		}


		private ExtraCellValidateResult FlagCheckToFlipNextCell(int row,
		                                                                            int col,
		                                                                            CellStatus currentTag,
		                                                                            CellStatus tagsLookingFor) {
		  // if legal place & empty - BAD place
		  if (this.board.LegalPlaceInBoard(row, col) && this.board.GetCellStatus(row, col) == CellStatus.E.ordinal()) {
		    return ExtraCellValidateResult.BAD;
		  }
		  // if legal place & filled with currentTag - GOOD place
		  if (this.board.LegalPlaceInBoard(row, col) && this.board.GetCellStatus(row, col) == currentTag.ordinal()) {
		    return ExtraCellValidateResult.GOOD;
		  }
		  // if legal place & filled with the tag we look for we have to check again the next cell
		  if (this.board.LegalPlaceInBoard(row, col) && this.board.GetCellStatus(row, col) == tagsLookingFor.ordinal()) {
		    return ExtraCellValidateResult.AGAIN;
		  }
		  // default, if not legal place for example
		  return ExtraCellValidateResult.BAD;
		}

		public void FlipSlots(int row, int col, CellStatus flipTo) {
		  Board b = this.board;
		  // clear the slots to flip ArrayList, in order to not flip an old slot unintentionally
		  this.finalSlotsToFlip.clear();
		  // receives all the slots we have to flip due to recent placement of the tag
		  ArrayList<Slot> slotsToFlip = SlotsToFlip(flipTo, row, col);
		  CellStatus flipFrom;
		  if (flipTo == CellStatus.X) {
		    flipFrom = CellStatus.O;
		  } else {
		    flipFrom = CellStatus.X;
		  }
		  // for each slot in slot_to_flip ArrayList
		  for (int i = 0; i < slotsToFlip.size(); i++) {
		    // remove from old ArrayList (also known as "flipFrom" ArrayList)
		    if (flipFrom == CellStatus.X) {
		      // remove slotsToFlip[i] from board.GetXSlots ArrayList
		      // if it is indeed in the ArrayList, erase it
		      int locationToOmit = slotsToFlip.get(i).LocationInArrayList(b.GetXSlots());
		      ArrayList<Slot> newXSlots = new ArrayList<Slot>(64);
		      // if locationToOmit exist
		      if (locationToOmit != -1) {
		        // copy every X slot to a new ArrayList without slot at [location to omit]
		        for (int k = 0; k < b.GetXSlots().size(); k++) {
		          if (k != locationToOmit) {
		            newXSlots.add(b.GetXSlots().get(k));
		          }
		        }
		      }
		      // update the Board X slots to the new ArrayList
		      b.SetXSlots(newXSlots);
		    } else {
		      // the same for O slots
		      int locationToOmit = slotsToFlip.get(i).LocationInArrayList(b.GetOSlots());
		      ArrayList<Slot> newOSlots = new ArrayList<Slot>(64);
		      // if locationToOmit exist
		      if (locationToOmit != -1) {
		        for (int k = 0; k < b.GetOSlots().size(); k++) {
		          if (k != locationToOmit) {
		            newOSlots.add(b.GetOSlots().get(k));
		          }
		        }
		      }
		      b.SetOSlots(newOSlots);
		    }
		    // flip it
		    b.SetCellStatus(slotsToFlip.get(i).GetRow(), slotsToFlip.get(i).GetCol(), flipTo);
		  }
		}


		public Logic CopyLogic(Board b) {
		  RegularLogic copyOfRl = new RegularLogic(b);
		 // copyOfRl.board = b;
		  return copyOfRl;
		}

}

