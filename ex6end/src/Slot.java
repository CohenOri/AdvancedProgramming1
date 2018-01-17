import java.util.ArrayList;

public class Slot {
    private int row;
    private int col;
    private CellStatus status;

    /**
     * Create a slot with E (Empty status)
     *
     * @param row
     * @param col
     */
    public Slot(int row, int col) {
        this.row = row;
        this.col = col;
        this.status = CellStatus.E;
    }

    /**
     * Create slot with given status
     *
     * @param row
     * @param col
     * @param status
     */
    public Slot(int row, int col, CellStatus status) {
        this.row = row;
        this.col = col;
        this.status = status;
    }

    public Slot(String string) {
        String[] parts = string.split(",");
        String row = parts[0];
        String col = parts[1];
        this.row = Integer.parseInt(row);
        this.col = Integer.parseInt(col);
        this.status = CellStatus.E;
    }

    /**
     * Print in the (row,col) format
     */
    public void Print() {
        System.out.print("(" + this.row + ", " + this.col + ")");
    }

    /**
     * @return row of slot
     */
    public int GetRow() {
        return this.row;
    }

    /**
     * @param row to set
     */
    public void SetRow(int row) {
        this.row = row;
    }

    /**
     * @return col of slot
     */
    public int GetCol() {
        return this.col;
    }

    /**
     * @param col to set
     */
    public void SetCol(int col) {
        this.col = col;
    }

    /**
     * Prints the status of the slot (E, X, O)
     */
    public void PrintStatus() {
        if (this.status == CellStatus.E) {
            System.out.print("cell status is: E\n");
        } else if (this.status == CellStatus.X) {
            System.out.print("cell status is: X\n");
        } else if (this.status == CellStatus.O) {
            System.out.print("ccell status is: O\n");
        }
    }

    /**
     * @return status of the slot
     */
    public CellStatus GetCellStatus() {
        return this.status;
    }

    /**
     * @param v ArrayList
     * @return if the slot exist in the ArrayList
     */
    public boolean ExistInArrayList(ArrayList<Slot> v) {
        for (int i = 0; i < v.size(); i++) {
            if (this.row == v.get(i).GetRow() && this.col == v.get(i).GetCol() &&
                    this.status == v.get(i).GetCellStatus()) {
                return true;
            }
        }
        return false;
    }

    /**
     * @param v ArrayList
     * @return the index (location) of the slot in the given ArrayList
     */
    public int LocationInArrayList(ArrayList<Slot> v) {
        for (int i = 0; i < v.size(); i++) {
            if (this.row == v.get(i).GetRow() && this.col == v.get(i).GetCol()
                    && this.status == v.get(i).GetCellStatus()) {
                return i;
            }
        }
        return -1;
    }

    /**
     * @return deep copy for slot.
     */
    public Slot CopySlot() {
        Slot copyOfSlot = new Slot(this.GetRow(), this.GetCol(), this.GetCellStatus());
        return copyOfSlot;
    }
}
