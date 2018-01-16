import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Cell;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ResourceBundle;

public class GameController implements Initializable {
    private static final int PLAYER1 = 1;
    private static final int PLAYER2 = 2;

    @FXML private HBox root;
    @FXML private Text currentPlayer;
    @FXML private Text player1Score;
    @FXML private Text player2Score;
    @FXML private Text message;
    @FXML private Button backToMenuButton;


    private GameBoardController gameBoardController;
    private double mouseXVal;
    private double mouseYVal;
    private CellStatus curentPlayerVal;
    private String messageVal;

    private int firstPlayer;
    private int boardSize;


    private ImageView playerOneTag;
    private ImageView playerTwoTag;

    @Override
    public void initialize(URL location, ResourceBundle resources) {

        // read the settings from the file
        GameFlow gameFlow = readGameFlowFromFile();

        this.curentPlayerVal = CellStatus.X;
        this.messageVal = "";

        // create the gui board
        this.gameBoardController = new GameBoardController(gameFlow.GetBoard());
        this.gameBoardController.setPrefWidth(400);
        this.gameBoardController.setPrefHeight(400);
        root.getChildren().add(0, this.gameBoardController);
        this.gameBoardController.draw();

        // listeners to hold windows resize
        root.widthProperty().addListener((observable, oldValue, newValue) -> {
            double boardNewWidth = newValue.doubleValue() - 200;
            this.gameBoardController.setPrefWidth(boardNewWidth);
            this.gameBoardController.draw();
        });

        root.heightProperty().addListener((observable, oldValue, newValue) -> {
            this.gameBoardController.setPrefHeight(newValue.doubleValue() - 40);
            this.gameBoardController.draw();
        });

        // listeners...
        gameBoardController.addEventFilter(MouseEvent.MOUSE_PRESSED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                mouseXVal = mouseEvent.getX();
                mouseYVal = mouseEvent.getY();
                int posX = (int) ((mouseXVal / gameBoardController.getWidth()) * gameBoardController.getBoard().getSize());// + 1;
                int posY = (int) ((mouseYVal / gameBoardController.getHeight()) * gameBoardController.getBoard().getSize());// + 1;

                boolean legalSlot = gameFlow.playOneTurn(new Slot(posX, posY));
                if(!legalSlot){
                    setMessage("Illigal move!");
                }
                if(gameFlow.GameOver()){
                    gameOver("string_whos the wnner");
                }
            }
        });

        // define players imageView
        this.gameBoardController.setPlayerOneTag(this.playerOneTag);
        this.gameBoardController.setPlayerTwoTag(this.playerTwoTag);

        // initialize the game
       // gameFlow.initializeGame();
    }

    public void draw() {
        switch (this.curentPlayerVal.ordinal()) {
            case PLAYER1:
                this.currentPlayer.setText("Player1");
                break;
            case PLAYER2:
                this.currentPlayer.setText("Player2");
                break;
        }
        this.player1Score.setText("" + this.gameBoardController.getBoard().getNumOfCells(this.PLAYER1));
        this.player2Score.setText("" + this.gameBoardController.getBoard().getNumOfCells(this.PLAYER2));
        this.gameBoardController.draw();
        this.message.setText(this.messageVal);
        this.messageVal = "";
    }

    public GameBoardController getGameBoardController() {
        return gameBoardController;
    }

    public double getMouseXVal() {
        return mouseXVal;
    }

    public double getMouseYVal() {
        return mouseYVal;
    }

    public void setCurrentPlayer(Text currentPlayer) {
        this.currentPlayer = currentPlayer;
    }

    public void setMessage(String message) {
        this.message = new Text();
        this.message.setText(message);
    }


    // if not copy SettingsController code
    public void menu() {
        SettingsController s = new SettingsController();
        s.goBackToMenu();
    }

    public void gameOver(String winnerText) {
        try {
            StackPane root = (StackPane)FXMLLoader.load(getClass().getResource("DeclareWinner.fxml"));
            Label label = (Label) root.getChildren().get(0);
            label.setText(winnerText);
            Stage stage = new Stage();
            stage.setTitle("Game Over!");
            Scene scene = new Scene(root, 600, 400);
            stage.setScene(scene);
            stage.show();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }


    private GameFlow readGameFlowFromFile() {

        // read the setting from file
        // Yana...
        File settingsFile = new File("Settings.txt");
		BufferedReader is = null;
        try {
			is = new BufferedReader(new InputStreamReader(new FileInputStream("Settings.txt")));
			String line ;
			 while ((line = is.readLine()) != null ) { // ’null ’->no more data in the stream
				 String[] parts = line.split(":");
				 String key = parts[0];//configurations.
				 String val = parts[1];//the data user instert.
				 if (key.equals("firstPlayer")) {
				 //if first player is 1 means x starts.
					 this.firstPlayer = Integer.parseInt(val);
				 } else if(key.equals("firstImage:")) {
					 this.playerOneTag = new ImageView(getClass().getResource(val).toExternalForm()); 
				 } else if(key.equals("SecondImage")) {
					 this.playerTwoTag = new ImageView(getClass().getResource(val).toExternalForm()); 
				 } else if(key.equals("boardSize")) {
				 //set boards size.
					 this.boardSize = Integer.parseInt(val);
				 }
			 }
        } catch (Exception e) {
            // assign default values
            this.firstPlayer = PLAYER1;
            this.playerOneTag = new ImageView();
            this.playerOneTag.setImage(new Image(new File("blackTag.png").toURI().toString()));
            this.playerTwoTag = new ImageView();
            this.playerTwoTag.setImage(new Image(new File("greyTag.png").toURI().toString()));
        } finally {
    		if( is != null ){ // Exception might have happened at constructor
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
        if (firstPlayer == PLAYER1) {
            Player1 = new TerminalPlayer(CellStatus.X);
            Player2 = new TerminalPlayer(CellStatus.O);
        } else {
            Player1 = new TerminalPlayer(CellStatus.O);
            Player2 = new TerminalPlayer(CellStatus.X);
        }
        Board board = new Board(boardSize, boardSize);
        Logic logicGame = new Regular(board);
        // create the game flow
        GameFlow gameFlow = new GameFlow(logicGame, board, Player1, Player2, drawer);
        return gameFlow;
        }
    }




