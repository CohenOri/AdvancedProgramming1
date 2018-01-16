import java.util.ArrayList;
import java.util.Vector;

 public interface Logic {
		  /**
		   * @return pointer to an array including all the possible slots to place tag in.
		   */
	 public ArrayList<Slot> SlotsToPlace(CellStatus cellStatus);
		  /**
		   * receives the row & col of the now placed tag, and the status we
		   * are going to flip (if we placed X then we want to flip O)
		   * @param row
		   * @param col
		   * @param flipTo
		   */
	 public void FlipSlots(int row, int col, CellStatus flipTo);
		  /**
		   * deep copy for logic.
		   * @param b for copy.
		   */
	 public Logic CopyLogic(Board b);
}
