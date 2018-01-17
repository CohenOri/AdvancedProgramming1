import javafx.scene.text.Text;

import java.util.ArrayList;

public class GUI {

    private GameController gameController;

    /**
     * Constructor.
     * this class used to connecr between action of user and respond.
     *
     * @param gameController
     */
    public GUI(GameController gameController) {
        this.gameController = gameController;
    }

    /**
     * call draw function of the game.
     */
    public void drawGame() {
        this.gameController.draw();
    }

    /**
     * @param message to print on board.
     */
    public void drawMessage(String message) {
        this.gameController.setMessage(message);
    }

    /**
     * @param player who playes next turn.
     */
    public void setPlayer(CellStatus player) {
        this.gameController.setCurrentPlayer(player);
    }

    /**
     * @param possibleSlots array to print on board.
     */
    public void drawPossibleMoves(ArrayList<Slot> possibleSlots) {
        if (possibleSlots.size() == 0) {
            this.gameController.setMessage("No possible moves\nClick on Screen");
        }
        this.gameController.getGameBoardController().setPossibleMoves(possibleSlots);
    }

}
