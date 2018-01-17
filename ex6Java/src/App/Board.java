package App;

import java.util.ArrayList;

public class Board {
    private ArrayList<Slot> oSlots;
    private ArrayList<Slot> xSlots;
    private CellStatus[][] board;
    private int rows;
    private int cols;

    /**
     * constutoe for board. create matrix of slots.
     *
     * @param numOfRows
     * @param numOfCols
     */
    public Board(int numOfRows, int numOfCols) {
        // num of rows
        // num of cols
        this.cols = numOfCols;
        this.rows = numOfRows;
        this.board = new CellStatus[numOfRows][numOfCols];
        this.oSlots = new ArrayList<Slot>(64);
        this.xSlots = new ArrayList<Slot>(64);
        for (int i = 1; i <= this.rows; i++) {
            for (int j = 1; j <= this.cols; j++) {
                this.setCellStatus(i, j, CellStatus.E);
            }
        }
    }

    /**
     * set size of board;
     *
     * @param row size.
     * @param col size.
     */
    public void setSize(int row, int col) {
        this.rows = row;
        this.cols = col;
    }

    /**
     * @param xLocation to get
     * @param yLocation to get
     * @return the status of the given cell (Empty, O, X)
     */
    public int getCellStatus(int xLocation, int yLocation) {
        if (xLocation >= 1 && xLocation <= this.numOfRows()
                && yLocation >= 1 && yLocation <= this.numOfCols()) {
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
     *
     * @param xLocation of the cell
     * @param yLocation of the cell
     * @param status    - the new status to set (E, O, X)
     */
    public void setCellStatus(int xLocation, int yLocation, CellStatus status) {
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
    public int numOfRows() {
        return this.rows;
    }

    /**
     * @return number of cols
     */
    public int numOfCols() {
        return this.cols;
    }

    /**
     * @reutrn ArrayList slots for o
     */
    public ArrayList<Slot> getOSlots() {
        return this.oSlots;
    }

    /**
     * @reutrn ArrayList slots for x
     */
    public ArrayList<Slot> getXSlots() {
        return this.xSlots;
    }

    /**
     * @reutrn ArrayList slots for x
     */
    public ArrayList<Slot> getSlotsOfPlayer(CellStatus player) {
        if (player == CellStatus.X) {
            return this.xSlots;
        } else {
            return this.oSlots;
        }
    }

    /**
     * @param oSlots setOSlots
     */
    public void setOSlots(ArrayList<Slot> oSlots) {
        this.oSlots = oSlots;
    }

    /**
     * @param xSlots setXSlots
     */
    public void setXSlots(ArrayList<Slot> xSlots) {
        this.xSlots = xSlots;
    }

    /**
     * set Slots Of given App.Player
     *
     * @param player
     * @param slots
     */
    public void setSlotsOfPlayer(CellStatus player, ArrayList<Slot> slots) {
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
    public boolean legalPlaceInBoard(int row, int col) {
        return (row <= numOfRows() && row > 0
                && col <= numOfCols() && col > 0);
    }

    /**
     * @return deep copy of the board.
     */
    public Board copyBoard() {
        Board copyOfBoard = new Board(this.rows, this.cols);
        copyOfBoard.board = this.board;
        copyOfBoard.xSlots = this.xSlots;
        copyOfBoard.oSlots = this.oSlots;
        return copyOfBoard;
    }

    /**
     * check if given slot can placed on board.
     * @param slot to check.
     * @return boolean.
     */
    public boolean legalSlotInBoard(Slot slot) {
        return (slot.GetRow() <= numOfRows() && slot.GetRow() > 0
                && slot.GetCol() <= numOfCols() && slot.GetCol() > 0);
    }

    /**
     * @return size of the board.
     */
    public double getSize() {
        return this.cols;
    }

    /**
     * @param player12 number symbol of plyaer. 1 for x, 2 for o.
     * @return string represent number of slots on the board.
     */
    public String getNumOfCells(int player12) {
        if (player12 == 1) {
            return "" + this.xSlots.size();
        }
        return "" + this.oSlots.size();
    }

    /**
     * get cells status. if empty. x or o.
     *
     * @param i row.
     * @param j col.
     * @return the status.
     */
    public CellStatus getStatusOfCell(int i, int j) {
        return this.board[i][j];
    }

}
