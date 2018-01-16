import javafx.scene.text.Text;

import java.util.ArrayList;

public class GUI {

    private GameController gameController;
    //private GameBoardController gameBoardController;

    public GUI(GameController gameController){
        this.gameController = gameController;
        //this.gameBoardController = gameBoardController;
    }
    

    public void drawGame() {
        this.gameController.draw();
    }

    public void drawGameOver(CellStatus player) {
        switch (player.ordinal()) {
            case 1:
                this.gameController.gameOver("Congrats Player1 You are the winner!");
                break;
            case 2:
                this.gameController.gameOver("Congrats Player2 You are the winner!");
                break;
            default:
                this.gameController.gameOver("Its a tie!");
                break;
        }
    }

    public void drawMessage(String message) {
        this.gameController.setMessage(message);
    }
    public void SetPlayer(CellStatus player) {
    	this.gameController.SetCurrentPlayer(player);
    }
    public void drawPlayerMoveTitle(CellStatus cellStatus) {
    	Text player = new Text();
    	if(cellStatus == CellStatus.X) {
    		player.setText("player1"); 
    	} else {
    		player.setText("player2"); 
    	}
        this.gameController.setCurrentPlayer(player);
    }

    public void drawPossibleMovesTitle(ArrayList<Slot> possibleSlots) {
        if (possibleSlots.size() == 0) {
            this.gameController.setMessage("No possible moves\nClick on Screen");
        }
        this.gameController.getGameBoardController().setPossibleMoves(possibleSlots);
    }

}
