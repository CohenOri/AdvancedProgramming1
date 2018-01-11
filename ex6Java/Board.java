import java.util.ArrayList;
import java.util.List;
import java.util.Vector;


public class Board {
	private Vector<Slot>  oSlots;
	private Vector<Slot> xSlots;
	private CellStatus[][] board;
	private int rows;
	private int cols;
	
	public Board(int numOfRows, int numOfCols) {
		// num of rows
	    // num of cols
		this.cols = numOfCols;
		this.rows = numOfRows;
		this.board = new CellStatus[numOfRows][numOfCols];
	}
	  /**
	   * Print method which prints the board as requested.
	   */
	  public void Print() {
		  System.out.print( " |");
		    for (int i = 1; i <= NumOfCols(); i++) {
		    	System.out.print(" " + i + " |");
		    }
		    System.out.print( "\n");
		    System.out.print("--");
		    for (int i = 0; i < NumOfCols(); i++) {
		    	System.out.print( "----");
		    }
		    System.out.print("\n");
		    for (int i = 0; i < NumOfCols(); i++) {
		    	System.out.print( "" + (i + 1) + "|");
		        for (int j = 0; j < NumOfRows(); j++) {
		        	System.out.print( " ");
		            switch (board[i][j].ordinal()) {
		                case 0:
		                	System.out.print( " ");
		                    break;
		                case 1:
		                	System.out.print("O");
		                    break;
		                case 2:
		                	System.out.print( "X");
		                    break;
		            }
		            System.out.print( " |");
		        }
		        System.out.print("\n");
		        System.out.print("--");
		        for (int j = 0; j < NumOfCols(); j++) {
		        	System.out.print( "----");
		        }
		        System.out.print("\n");
		    }
	  }
	  /**
	   * @param xLocation to get
	   * @param yLocation to get
	   * @return the status of the given cell (Empty, O, X)
	   */
	  public int GetCellStatus(int xLocation, int yLocation) {
		  int a;
		    if (xLocation >= 1 && xLocation <= this.NumOfRows()
		            && yLocation >= 1 && yLocation <= this.NumOfCols()) {
		            // -1 because array starting from 0
		            return this.board[xLocation - 1][yLocation - 1].ordinal();
		        }
		      //  cout << "Illegal row or col" << endl;
		        return -1;
	  }
	  /**
	   * Set the given cell new status.
	   * (if given (4,4) location set new status to board[3][3] location
	   * since we print from 1,1 and not 0,0).
	   * @param xLocation of the cell
	   * @param yLocation of the cell
	   * @param status - the new status to set (E, O, X)
	   */
	  public void SetCellStatus(int xLocation, int yLocation, CellStatus status) {
		    // if X or O add it to the vectors which holds list of X/O Slots
		    if (status == CellStatus.X) {
		        this.xSlots.add((new Slot(xLocation, yLocation, status)));
		    } else if (status == CellStatus.O) {
		        this.oSlots.add(new Slot(xLocation, yLocation, status));
		    }
		    // -1 because array starting from 0
		    this.board[xLocation - 1][yLocation - 1] = status;
	  }
	  
	  /**
	   * @return number of rows
	   */
	  public int NumOfRows() {return this.rows; }
	  /**
	   * @return number of cols
	   */
	  public int NumOfCols() {return this.cols; }
	  /**
	   * @reutrn vector slots for o
	   */
	  public Vector<Slot> GetOSlots() {return this.oSlots; }
	  /**
	   * @reutrn vector slots for x
	   */
	  public Vector<Slot> GetXSlots() {return this.xSlots;}
	  /**
	   * @reutrn vector slots for x
	   */
	 public Vector<Slot> GetSlotsOfPlayer(CellStatus player){
		    if (player == CellStatus.X) {
		        return this.xSlots;
		    } else {
		        return this.oSlots;
		    }
	 }
	 public void SetOSlots(Vector<Slot> oSlots) {this.oSlots = oSlots;}
	 public void SetXSlots(Vector<Slot> xSlots) {this.xSlots = xSlots;}
	 
	 public void SetSlotsOfPlayer(CellStatus player, Vector<Slot> slots) {
		    if (player == CellStatus.X) {
		        this.xSlots = slots;
		    } else {
		        this.oSlots = slots;
		    }
		}
	 
	  /**
	   * @param row
	   * @param col
	   * @return if its legal place in board
	   */
	 public boolean LegalPlaceInBoard(int row, int col) {
		    return (row <= NumOfRows() && row > 0
		            && col <= NumOfCols() && col > 0);
	 }
	  /**
	   * @return deep copy of the board.
	   */
	 public Board CopyBoard() {
		    Board copyOfBoard = new Board(this.rows, this.cols);
		    copyOfBoard.board = this.board;
		    copyOfBoard.xSlots = this.xSlots;
		    copyOfBoard.oSlots = this.oSlots;
		    return copyOfBoard;
	 }
	 
	 public boolean LegalSlotInBoard(Slot slot) {
		    return (slot.GetRow() <= NumOfRows() && slot.GetRow() > 0
		            && slot.GetCol() <= NumOfCols() && slot.GetCol() > 0);
		}

}
