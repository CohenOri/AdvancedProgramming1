import java.util.Vector;


public class RegularLogic implements Logic {
	
	  private  Board board;
	  private	  Vector<Slot> finalSlotsToFlip;
			/**
			 * @param b create logic using a pointer to board
			 */
	  public  RegularLogic(Board b) {
		  this.board = b;
	  }
		  /**
		   * @param cell_status tag
		   * @return vector with all the slots available to place the given tag
		   */
	  public Vector<Slot> SlotsToPlace(CellStatus cellStatus) {
		  Board b = this.board;
		  Vector<Slot> overallSlotsToPlaceList = null;
		    /*
		     * iterate over every players in the board, find the PossibleSlots for him
		     * add it to overall slots to place list only if it doesn't in it already
		     * (overallSlotsToPlaceList is free of duplicates)
		     */
		    for (int i = 0; i < b.GetSlotsOfPlayer(cellStatus).size(); i++) {
		      Slot s = b.GetSlotsOfPlayer(cellStatus).get(i);
		      Vector<Slot> v = PossibleSlotsFor(s.GetCellStatus(), s.GetRow(), s.GetCol());
		      for (int j = 0; j < v.size(); i++) {
		        Slot slot = v.get(j);
		        // verify that each Slot inserted only once (prevent duplicates)
		        if (!slot.ExistInVector(overallSlotsToPlaceList)) {
		          overallSlotsToPlaceList.add(slot);
		        }
		      }
		    }
		  return overallSlotsToPlaceList;
	  }
	  
		  /**
		   * Flips the slots which should be flipped due to the recent placement
		   * of the given tag
		   * @param row of the recently placed tag
		   * @param col of the recently placed tag
		   * @param flip_to the status of the recently placed tag
		   */
	  public void FlipSlots(int row, int col, CellStatus flipTo) {
		  Board b = this.board;
		  // clear the slots to flip vector, in order to not flip an old slot unintentionally
		  this.finalSlotsToFlip.clear();
		  // receives all the slots we have to flip due to recent placement of the tag
		  Vector<Slot> slotsToFlip = SlotsToFlip(flipTo, row, col);
		  CellStatus flipFrom;
		  if (flipTo == CellStatus.X) {
		    flipFrom = CellStatus.O;
		  } else {
		    flipFrom = CellStatus.X;
		  }
		  // for each slot in slot_to_flip vector
		  for (int i = 0; i < slotsToFlip.size(); i++) {
		      int locationToOmit = slotsToFlip.get(i).LocationInVector(b.GetSlotsOfPlayer(flipFrom));
		      Vector<Slot> newSlots = null;
		      // if locationToOmit exist
		      if (locationToOmit != -1) {
		        // copy every players slot to a new vector without slot at [location to omit]
		        for (int k = 0; k < b.GetSlotsOfPlayer(flipFrom).size(); k++) {
		          if ((int)k != locationToOmit) {
		            newSlots.add(b.GetSlotsOfPlayer(flipFrom).get(i));
		          }
		        }
		      }
		      // update the Board players slots to the new vector
		    b.SetSlotsOfPlayer(flipFrom, newSlots);
		    // flip it
		    b.SetCellStatus(slotsToFlip.get(i).GetRow(), slotsToFlip.get(i).GetCol(), flipTo);
		  }
	  }


		  /**
		   * @param currentTag
		   * @param row
		   * @param col
		   * @return vector with all the possible slots to another tag (same status) unlocked because of
		   * the given tag
		   */
		 private Vector<Slot> PossibleSlotsFor(CellStatus currentTag, int row, int col) {
			  CellStatus tagsLookingFor = null;
			  Vector<Slot> possibleSlots = null;

			  if (currentTag == CellStatus.X) {
			    tagsLookingFor = CellStatus.O;
			  } else if (currentTag == CellStatus.O){
			    tagsLookingFor = CellStatus.X;
			  }
			  
			  OneDierectionSlots(row - 1, col - 1, row - 2, col - 2, possibleSlots,
					  currentTag, tagsLookingFor, Operation.MINUS, Operation.MINUS, false);
			  OneDierectionSlots(row - 1, col, row - 2, col, possibleSlots, currentTag,
					  tagsLookingFor, Operation.MINUS, Operation.NOTHING,false);
			  OneDierectionSlots(row - 1, col + 1, row - 2, col + 2, possibleSlots,
					  currentTag, tagsLookingFor, Operation.MINUS, Operation.PLUS, false);
			  OneDierectionSlots(row, col - 1, row, col - 2, possibleSlots, currentTag,
					  tagsLookingFor, Operation.NOTHING, Operation.MINUS, false);
			  OneDierectionSlots(row, col + 1, row, col + 2, possibleSlots, currentTag,
					  tagsLookingFor, Operation.NOTHING, Operation.PLUS, false);
			  OneDierectionSlots(row + 1, col - 1, row + 2, col - 2, possibleSlots,
					  currentTag, tagsLookingFor, Operation.PLUS, Operation.MINUS, false);
			  OneDierectionSlots(row + 1, col, row + 2, col, possibleSlots, currentTag,
					  tagsLookingFor, Operation.PLUS, Operation.NOTHING, false);
			  OneDierectionSlots(row + 1, col + 1, row + 2, col + 2, possibleSlots,
					  currentTag, tagsLookingFor, Operation.PLUS, Operation.PLUS, false);
			  
			  return possibleSlots;
		 }

		/**
		 * this function calls recirsuve function to check one direction if slots can flipped.
		 * it also can detemine if slots should be flipped in process or not.
		 * @param row place of slot to check if enemy or empty.
		 * @param col place of slot to check if enemy or empty.
		 * @param nextRow place of slot near the row val
		 * @param nextCol place of slot near the col val
		 * @param slotsVector will contain list of slots.
		 * @param player enum symbol
		 * @param enemy enum symbol
		 * @param rowOperation minus plus or nothing
		 * @param colOperation minus plus or nothing
		 * @param check bool if we just serach for liggal slots but not flipping-true.
		 *
		 */
		 private void OneDierectionSlots(int row, int col, int nextRow, int nextCol, Vector<Slot> slotsVector,
				  	  	  CellStatus player, CellStatus enemy, Operation rowOperation, Operation colOperation, boolean check) {
				if (this.board.LegalPlaceInBoard(row,col) &&
						this.board.GetCellStatus(row, col) == enemy.ordinal()) {
					  if (check == true) {
					  slotsVector.add(new Slot(row, col, enemy));
					  RecursiveCheckNextCell(nextRow, nextCol, slotsVector,
							  enemy, player,rowOperation, colOperation,
					                              player);
					  } else {
						  RecursiveCheckNextCell(nextRow, nextCol, slotsVector, enemy,
								  player, rowOperation, colOperation, CellStatus.E);
					  }
				  }
		 }
		  /**
		   * @param currentTag
		   * @param row
		   * @param col
		   * @return vector with slots we have to flip because of the placement
		   * of the given tag
		   */
		 private Vector<Slot> SlotsToFlip(CellStatus currentTag, int row, int col) {
			  CellStatus tagsLookingFor;
			  Vector<Slot> tempSlotsToFlip = null;
			  if (currentTag == CellStatus.X) {
			    tagsLookingFor = CellStatus.O;
			  } else {
			    tagsLookingFor = CellStatus.X;
			  }

			  OneDierectionSlots(row - 1, col - 1, row - 2, col - 2, tempSlotsToFlip,
					  currentTag, tagsLookingFor, Operation.MINUS, Operation.MINUS, true);
			  tempSlotsToFlip.clear();
			  OneDierectionSlots(row - 1, col, row - 2, col, tempSlotsToFlip, currentTag,
					  tagsLookingFor, Operation.MINUS, Operation.NOTHING, true);
			  tempSlotsToFlip.clear();
			  OneDierectionSlots(row - 1, col + 1, row - 2, col + 2, tempSlotsToFlip,
					  currentTag, tagsLookingFor, Operation.MINUS, Operation.PLUS, true);
			  tempSlotsToFlip.clear();
			  OneDierectionSlots(row, col - 1, row, col - 2, tempSlotsToFlip, currentTag,
					  tagsLookingFor, Operation.NOTHING, Operation.MINUS, true);
			  tempSlotsToFlip.clear();
			  OneDierectionSlots(row, col + 1, row, col + 2, tempSlotsToFlip, currentTag,
					  tagsLookingFor, Operation.NOTHING, Operation.PLUS, true);
			  tempSlotsToFlip.clear();
			  OneDierectionSlots(row + 1, col - 1, row + 2, col - 2, tempSlotsToFlip,
					  currentTag, tagsLookingFor, Operation.PLUS, Operation.MINUS, true);
			  tempSlotsToFlip.clear();
			  OneDierectionSlots(row + 1, col, row + 2, col, tempSlotsToFlip, currentTag,
					  tagsLookingFor, Operation.PLUS, Operation.NOTHING, true);
			  tempSlotsToFlip.clear();
			  OneDierectionSlots(row + 1, col + 1, row + 2, col + 2, tempSlotsToFlip,
					  currentTag, tagsLookingFor, Operation.PLUS, Operation.PLUS, true);
			  tempSlotsToFlip.clear();

			  return this.finalSlotsToFlip;
		 }
		  /**
		   * Return if given cell is good, bad or we have to check the also the next cell (again)
		   * to place certain tag - returns a flag.
		   * if the next cell filled with the tag we look for, we should check another cell (AGAIN)
		   * if the next cell filled with the same tag as given tag (XOX) - nothing to do (BAD place)
		   * if the next cell is empty, it is a GOOD place
		   * @param row
		   * @param col
		   * @param currentTag
		   * @param tagsLookingFor
		   * @return flag, cell is GOOD, BAD, or we have to check AGAIN
		   */
		 private  ExtraCellValidateResult FlagCheckNextCell(int row, int col,CellStatus currentTag,
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


		  /**
		   * Return if given cell is good, bad or we have to check the also the next cell (again)
		   * so we have to flip all the slots between the start to end slots - returns a flag
		   * "end slot is: GOOD, BAD, AGAIN" if it is indeed GOOD we have to flip slots...
		   * if the next cell filled with the tag we look for, we should check another cell (AGAIN)
		   * if the next cell filled with the same tag as given tag (XOX) - GOOD place
		   * if the next cell is empty, it is a BAD place
		   * @param row
		   * @param col
		   * @param currentTag
		   * @param tagsLookingFor
		   * @return flag, cell is GOOD, BAD, or we have to check AGAIN
		   */
		 private ExtraCellValidateResult FlagCheckToFlipNextCell(int row, int col, CellStatus currentTag, CellStatus tagsLookingFor) {
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
		  /**
		   * Checks if a given cell is good to place tag and add it to the possible slot vector
		   * @param rowToCheck
		   * @param colToCheck
		   * @param slotsVector
		   * @param tagsLookingFor
		   * @param currentTag
		   * @param rowOperation
		   * @param colOperation
		   */

		 private void RecursiveCheckNextCell(int rowToCheck,
		                              int colToCheck,
		                              Vector<Slot> slotsVector,
		                              CellStatus tagsLookingFor,
		                              CellStatus currentTag,
		                              Operation rowOperation,
		                              Operation colOperation, CellStatus endTag) {
			  // decide whether its checking next cell to place or checks cell to flip
			  ExtraCellValidateResult condition = FlagCheckNextCell(rowToCheck, colToCheck, currentTag, tagsLookingFor);
			  if (endTag != CellStatus.E) {
			    condition = FlagCheckToFlipNextCell(rowToCheck, colToCheck, currentTag, tagsLookingFor);
			  }

			    if (condition == ExtraCellValidateResult.GOOD) {
			      // if checks "next cell to place"
			      if (endTag == CellStatus.E) {
			        // add to "possible slot" vector
			        slotsVector.add(new Slot(rowToCheck, colToCheck));
			      }
			      // if checks "cells to flip", add the tempSlotsToFlip to final_slotsToFlip
			      if (endTag != CellStatus.E) {
			        for (int k = 0; k < slotsVector.size(); k++) {
			          this.finalSlotsToFlip.add(slotsVector.get(k));
			        }
			      }
			    }
			    else if(condition == ExtraCellValidateResult.AGAIN) {
			      // we have to check extra cell
			      // if checks "cells to flip"
			      if (endTag != CellStatus.E) {
			        // add it "to_be_flipped" vector (don't mind the slot_vector name)
			        // if the end tag is not E (end tag is the current tag...)
			        slotsVector.add(new Slot(rowToCheck, colToCheck, tagsLookingFor));
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
			      RecursiveCheckNextCell(rowToCheck, colToCheck, slotsVector,
			                             tagsLookingFor, currentTag, rowOperation, colOperation, endTag);
			      // default - for example BAD slot - do nothing
			    }
			  }
		 
		  /**
		   * @param b - pointer to board which the new copy of logic (deep copy) should run on.
		   * @return RegularLogic object running on the given board
		   */
		 public Logic CopyLogic(Board b) {
			  RegularLogic copyOfRl = new RegularLogic(b);
			  copyOfRl.board = b;
			  return copyOfRl;
		 }
		  
}
