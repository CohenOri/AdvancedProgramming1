package GUI;

import App.*;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.net.URL;
import java.util.ResourceBundle;

public class GameController implements Initializable {

    @FXML
    private HBox root;
    @FXML
    private Text currentPlayer;
    @FXML
    private Text player1Score;
    @FXML
    private Text player2Score;
    @FXML
    private Text status;
    @FXML
    private Button backToMenuButton;
    private GameBoardController gameBoardController;
    private double mouseXVal;
    private double mouseYVal;
    private CellStatus currentPlayerVal;
    private int firstPlayer;
    private int boardSize;
    private String playerOneTagPath;
    private String playerTwoTagPath;

    @Override
    public void initialize(URL location, ResourceBundle resources) {

        // read the settings from the file
        GameFlow gameFlow = readGameFlowFromFile();

        // create the gui board.
        this.gameBoardController = new GameBoardController(gameFlow.GetBoard());
        this.gameBoardController.setPlayerOneTag(this.playerOneTagPath);
        this.gameBoardController.setPlayerTwoTag(this.playerTwoTagPath);
        this.gameBoardController.setPrefWidth(400);
        this.gameBoardController.setPrefHeight(400);
        root.getChildren().add(0, this.gameBoardController);
        this.gameBoardController.draw();

        // listeners in order to take care of windows resize
        root.widthProperty().addListener((observable, oldValue, newValue) -> {
            double boardNewWidth = newValue.doubleValue() - 200;
            this.gameBoardController.setPrefWidth(boardNewWidth);
            this.gameBoardController.draw();
        });

        root.heightProperty().addListener((observable, oldValue, newValue) -> {
            this.gameBoardController.setPrefHeight(newValue.doubleValue() - 40);
            this.gameBoardController.draw();
        });
        //draw settings
        this.draw();
        gameFlow.playOneTurn(null);

        // listeners...
        /**
         * this part gets players slot and flipped.
         */
        gameBoardController.addEventFilter(MouseEvent.MOUSE_PRESSED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                //get the place the user clicked.
                mouseXVal = mouseEvent.getX();
                mouseYVal = mouseEvent.getY();
                //calculate the slot values.
                int slotXVal = (int) (mouseXVal / gameBoardController.getWidth() * gameBoardController.getBoard().getSize());
                int sloyYval = (int) (mouseYVal / gameBoardController.getHeight() * gameBoardController.getBoard().getSize());
                //make a turn of the player.
                gameFlow.playOneTurn(new Slot(slotXVal + 1, sloyYval + 1)); // we add 1 because in the origins slots statrs from 1 not 0
                //check is its the end of game
                if (gameFlow.GameOver()) {
                    gameOver(gameFlow.EndGame());
                }

            }
        });

    }

    /**
     * Didn't help much. Helped a bit in bigger board but had bad infulence on smaller once therefore omitted.
     * Method to round digits to and remain as precise as possible.
     * round the number up to given places, exp. digitPrecision(200.3456, 2) - returns 200.35
     * @param value - the number to round
     * @param places - number of digits to round
     * @return the nubmer in the requested format
     */
    private double digitPrecision(double value, int places) {
        if (places < 0) {
            throw new IllegalArgumentException();
        }
        BigDecimal bd = new BigDecimal(value);
        bd = bd.setScale(places, RoundingMode.HALF_UP);
        return bd.doubleValue();
    }

    /**
     * @param player symbol who now playes.
     */
    public void setCurrentPlayer(CellStatus player) {
        this.currentPlayerVal = player;
    }

    /**
     * draw the inforamtion of the game.
     */
    public void draw() {
        //set who's turn it is.
        switch (this.currentPlayerVal.ordinal()) {
            case 1:
                this.currentPlayer.setText("Player1");
                break;
            case 2:
                this.currentPlayer.setText("Player2");
                break;
        }
        //set the score.
        this.player1Score.setText("" + this.gameBoardController.getBoard().getNumOfCells(CellStatus.X.ordinal()));
        this.player2Score.setText("" + this.gameBoardController.getBoard().getNumOfCells(CellStatus.O.ordinal()));
        this.gameBoardController.draw();
    }

    /**
     * @return board controller.
     */
    public GameBoardController getGameBoardController() {
        return gameBoardController;
    }

    /**
     * @return mouse value player clicked.
     */
    public double getMouseXVal() {
        return mouseXVal;
    }

    /**
     * @return mouse value player clicked.
     */
    public double getMouseYVal() {
        return mouseYVal;
    }

    /**
     * @param currentPlayer who now makes its turn.
     */
    public void setCurrentPlayer(Text currentPlayer) {
        this.currentPlayer = currentPlayer;
    }

    /**
     * @param message to display to player.
     */
    public void setMessage(String message) {
        this.status.setText(message);
    }


    // if not copy SettingsController code
    public void menu() {
        ScenesCallerUtility scu = new ScenesCallerUtility();
        scu.goToMenu(this.backToMenuButton);
    }

    /**
     * game over display.
     *
     * @param winnerTextMsg string with the message who won.
     */
    public void gameOver(String winnerTextMsg) {
        try {
            StackPane root = (StackPane) FXMLLoader.load(getClass().getResource("DeclareWinner.fxml"));
            Label label = (Label) root.getChildren().get(0);
            label.setText(winnerTextMsg);
            Stage stage = new Stage();
            stage.setTitle("Game Over!");
            Scene scene = new Scene(root, 400, 200);
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * read settings for the game from the file Settings.txt
     * if something with the file is wrong (user didn't set some setting)
     * or it doesn't exist assign default settings values and don't create any file.
     * @return
     */
    private GameFlow readGameFlowFromFile() {

        // read the setting from file
        BufferedReader is = null;
        Exception Exception = null;
        try {
            is = new BufferedReader(new InputStreamReader(new FileInputStream("Settings.txt")));
            String line;
            while ((line = is.readLine()) != null) { //null means no more data in the stream
                //split the string to two parts.
                String[] parts = line.split(":");
                String key = parts[0];//configurations.
                String val = parts[1];//the data user insert.
                if (val.equals("null")) throw new IOException();
                if (key.equals("firstPlayer")) {
                    //if first player is 1 means x starts.
                    this.firstPlayer = (int) Integer.parseInt(val);
                    if (firstPlayer == 1) {
                        this.currentPlayerVal = CellStatus.O;
                    } else {
                        this.currentPlayerVal = CellStatus.X;
                    }
                } else if (key.equals("firstImage")) {
                    this.playerOneTagPath = val; //path to image
                } else if (key.equals("SecondImage")) {
                    this.playerTwoTagPath = val; //path to image
                } else if (key.equals("boardSize")) {
                    //set boards size.
                    this.boardSize = (int) Integer.parseInt(val);
                } else {
                    break;
                }
            }

        } catch (Exception e) {
            // assign default values
            this.firstPlayer = CellStatus.O.ordinal();
            this.currentPlayerVal = CellStatus.O;
            this.playerOneTagPath = "blackTag.png";
            this.playerTwoTagPath = "greyTag.png";
            this.boardSize = 8;
        } finally {
            if (is != null) { // Exception might have happened at constructor
                try {
                    is.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        // initialize the game
        GUI drawer = new GUI(this);
        Player Player1;
        Player Player2;
        if (firstPlayer == CellStatus.O.ordinal()) {
            Player1 = new TerminalPlayer(CellStatus.O);
            Player2 = new TerminalPlayer(CellStatus.X);
        } else {
            Player1 = new TerminalPlayer(CellStatus.X);
            Player2 = new TerminalPlayer(CellStatus.O);
        }
        Board board = new Board(boardSize, boardSize);
        Logic logicGame = new RegularLogic(board);
        // create the game flow
        GameFlow gameFlow = new GameFlow(logicGame, board, Player1, Player2, drawer);
        return gameFlow;
    }
}




