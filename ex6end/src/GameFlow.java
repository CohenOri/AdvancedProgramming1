
public class GameFlow {

    private Logic logic;
    private Board board;
    private Player player[];
    private int turnCounter;
    private GUI drawer;

    /**
     * Class that holds all the information in order to run the game
     *
     * @param logic   - logic the game run with
     * @param board   - game board
     * @param player1
     * @param player2
     * @param drawer
     */
    public GameFlow(Logic logic, Board board, Player player1, Player player2, GUI drawer) {
        this.logic = logic;
        this.board = board;
        this.turnCounter = 0;
        //this.currentTurn = CellStatus.X;
        this.player = new Player[2];
        this.player[0] = player1;
        this.player[1] = player2;
        this.drawer = drawer;
        // some initialization
        board.setCellStatus(board.numOfRows() / 2, board.numOfCols() / 2, CellStatus.O);
        board.setCellStatus(board.numOfRows() / 2 + 1, board.numOfCols() / 2 + 1, CellStatus.O);
        board.setCellStatus(board.numOfRows() / 2 + 1, board.numOfCols() / 2, CellStatus.X);
        board.setCellStatus(board.numOfRows() / 2, board.numOfCols() / 2 + 1, CellStatus.X);
    }

    /**
     * @return if Game is Over.
     */
    public boolean GameOver() {
        if (this.logic.SlotsToPlace(CellStatus.X).size() != 0
                || this.logic.SlotsToPlace(CellStatus.O).size() != 0) {
            return false;
        }
        return true;
    }

    /**
     * return who is the winner by string.
     */
    public String EndGame() {
        Board b = this.board;
        // declare result
        if (b.getXSlots().size() > b.getOSlots().size()) {
            return "player 2 is the WINNER!!!";
        } else if (b.getXSlots().size() < b.getOSlots().size()) {
            return "Player 1 is the WINNER!!!";
        } else {
            return "It's a TIE!";
        }
    }

    /**
     * play players turn. if slot illigal-return false and don't change the turn;
     *
     * @param slot
     * @return
     */
    public boolean playOneTurn(Slot slot) {
        //if its null means its the first turn. print on board possible slots and return.
        if (slot == null) {
            this.drawer.drawPossibleMoves(this.logic.SlotsToPlace(this.player[this.turnCounter % 2].getEnumSymbol()));
            return false;
        }

        //make a move check if slot is legal. if not, print notification and don't move the turn to other player.
        boolean correctMove = this.player[this.turnCounter % 2].makeAMove(this.board, this.logic, slot);
        if (correctMove) {
            this.drawer.drawMessage("Excellent!");
            this.turnCounter++;
        } else this.drawer.drawMessage("Illegal move!!");

        //sent to drow possible slots for the next turn.
        this.drawer.drawPossibleMoves(this.logic.SlotsToPlace(this.player[this.turnCounter % 2].getEnumSymbol()));
        //prints on board whos turn it is.
        this.drawer.setPlayer(this.player[(this.turnCounter) % 2].getEnumSymbol());
        //if next turn have no moves, print him massage and move the turn back.
        if (this.logic.SlotsToPlace(this.player[this.turnCounter % 2].getEnumSymbol()).size() == 0) {
            this.turnCounter++;
            this.drawer.drawMessage("No Possible Moves!!! \n therefore the turn passes \n back to other player");
            this.drawer.drawPossibleMoves(this.logic.SlotsToPlace(this.player[this.turnCounter % 2].getEnumSymbol()));
            this.drawer.setPlayer(this.player[this.turnCounter % 2].getEnumSymbol());
        }

        this.drawer.drawGame();
        return correctMove;
    }

    /**
     * @return board.
     */
    public Board GetBoard() {
        return this.board;
    }
}
