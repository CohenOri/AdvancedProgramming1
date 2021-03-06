package App;

import java.util.Scanner;
import java.util.ArrayList;

public class TerminalPlayer implements Player {
    private CellStatus player;
    private char symbol;

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
     *
     * @return the slot the player chose to locate his tag at
     */
    public Slot play() {
        String str;
        Scanner sc = new Scanner(System.in);
        System.out.print("Please enter your row,col: ");
        str = sc.next();
        try {
            return new Slot(str);
        } catch (Exception exception) {
            System.out.print("Are you serious? enter something in the row, col format!");
            return play();
        }
    }

    /**
     * @return the symbol (X/O) of the player
     */
    public char getSymbol() {
        return this.symbol;
    }

    /**
     * Makes a move (play) over the board
     * receives the slot from the board-mouse and placing it
     * if no such slot can be plased-return false.
     *
     * @param b     board to make the move on
     * @param logic logic to boards using in order to place tags
     * @param slot
     * @return true if slot placed.
     */

    public boolean makeAMove(Board b, Logic logic, Slot slot) {
        ArrayList<Slot> v = logic.SlotsToPlace(this.player);
        if (slot.ExistInArrayList(logic.SlotsToPlace(this.player))) {
            b.setCellStatus(slot.GetRow(), slot.GetCol(), this.player);
            logic.FlipSlots(slot.GetRow(), slot.GetCol(), this.player);
            return true;
        } else {
            return false;
        }
    }

    /**
     * @return symbol (X/O) as App.CellStatus enum
     */
    public CellStatus getEnumSymbol() {
        return this.player;
    }

}
