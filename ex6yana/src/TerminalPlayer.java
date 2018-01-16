import java.util.Scanner;
import java.util.ArrayList;

public class TerminalPlayer implements Player {
	private CellStatus player;
	private  char symbol;
	    /**
	     * @param player the side/status of the player X or O
	     */
	public TerminalPlayer(CellStatus player) {
	    this.player = player;
	    if (player == CellStatus.X) {
	        this.symbol = 'X';
	    } else {
	        this.symbol = 'O';
	    }
	}

	    /**
	     * reads from terminal "row, col" & converts it to slot
	     * @return the slot the player chose to locate his tag at
	     */
	public  Slot Play() {
	    String str;
	    Scanner sc = new Scanner(System.in);
	    System.out.print("Please enter your row,col: ");
	    str = sc.next();
	    try {
	        return new Slot(str);
	    }
	    catch (Exception exception) {
		    System.out.print("Are you serious? enter something in the row, col format!");
	        return Play();
	    }
	}

	    /**
	     * @return the symbol (X/O) of the player
	     */
	public   char GetSymbol() {return this.symbol; }

	    /**
	     * Makes a move (play) over the board
	     * receives "play" from the terminal and placing it
	     * @param b board to make the move on
	     * @param logic logic to boards using in order to place tags
	     */

	public  boolean MakeAMove(Board b, Logic logic, Slot slot) {
		ArrayList<Slot> v = logic.SlotsToPlace(this.player);
		if (slot.ExistInArrayList(logic.SlotsToPlace(this.player))) {
	        b.SetCellStatus(slot.GetRow(), slot.GetCol(), this.player);
	        logic.FlipSlots(slot.GetRow(), slot.GetCol(), this.player);
	        return true;
	    } else {
	    	return false;
	    }
		}

	    /**
	     * @return symbol (X/O) as CellStatus enum
	     */
	public  CellStatus GetEnumSymbol() {return this.player;}



}
