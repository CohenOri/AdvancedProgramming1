import java.util.ArrayList;

import javafx.scene.image.ImageView;

public class Board {
	private ArrayList<Slot>  oSlots;
	private ArrayList<Slot> xSlots;
	private CellStatus[][] board;
	private int rows;
	private int cols;
	private ImageView player1;
	private ImageView player2;

	
	public Board(int numOfRows, int numOfCols) {
		// num of rows
	    // num of cols
		this.cols = numOfCols;
		this.rows = numOfRows;
		this.board = new CellStatus[numOfRows][numOfCols];
		this.oSlots = new ArrayList<Slot>(64);
		this.xSlots = new ArrayList<Slot>(64);
		for(int i = 1; i <= this.rows; i++) {
			for (int j = 1; j <= this.cols; j++) {
				this.SetCellStatus(i, j, CellStatus.E);
			}
		}
	}
	/**
	 * set size of board;
	 * @param row size.
	 * @param col size.
	 */
	public void SetSize(int row, int col) {
		this.rows = row;
		this.cols = col;
	}
	public void SetPlayerImage(String path, int player) {
		if(player == 1) {
			this.player1 =  new ImageView(getClass().getResource(path).toExternalForm());
		 } else if(player == 2) {
			 this.player2 =  new ImageView(getClass().getResource(path).toExternalForm());
		 }
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
		    // if X or O add it to the ArrayLists which holds list of X/O Slots
		    if (status == CellStatus.X) {
		        this.xSlots.add((new Slot(xLocation, yLocation, status)));
		    } else if (status == CellStatus.O) {
		    	Slot a = new Slot(xLocation, yLocation, status);
		        this.oSlots.add(a);
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
	   * @reutrn ArrayList slots for o
	   */
	  public ArrayList<Slot> GetOSlots() {return this.oSlots; }
	  /**
	   * @reutrn ArrayList slots for x
	   */
	  public ArrayList<Slot> GetXSlots() {return this.xSlots;}
	  /**
	   * @reutrn ArrayList slots for x
	   */
	 public ArrayList<Slot> GetSlotsOfPlayer(CellStatus player){
		    if (player == CellStatus.X) {
		        return this.xSlots;
		    } else {
		        return this.oSlots;
		    }
	 }
	 public void SetOSlots(ArrayList<Slot> oSlots) {this.oSlots = oSlots;}
	 public void SetXSlots(ArrayList<Slot> xSlots) {this.xSlots = xSlots;}
	 
	 public void SetSlotsOfPlayer(CellStatus player, ArrayList<Slot> slots) {
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
	 /**
	  * @return size of the board.
	  */
	public double getSize() {
		// TODO Auto-generated method stub
		return this.cols;
	}
	/**
	 * @param player12 number symbol of plyaer. 1 for x, 2 for o.
	 * @return string represent number of slots on the board.
	 */
	public String getNumOfCells(int player12) {
		if(player12 == 1) {
			return "" + this.xSlots.size();
		}
		return "" + this.oSlots.size();
	}
	/**
	 * get cells status. if empty. x or o.
	 * @param i row.
	 * @param j col.
	 * @return the status.
	 */
	public CellStatus GetStatusOfCell(int i, int j) {
		return this.board[i][j];
	}

}
