import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Slider;
import javafx.scene.control.ToggleGroup;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.URL;
import java.util.ResourceBundle;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class SettingsController implements Initializable {

    private static final int PLAYER1 = 1;
    private static final int PLAYER2 = 2;


    private ImageView playerOneTag;
    private ImageView playerTwoTag;
    private String forstImagePath;
    private String secondImagePath;
    private int firstPlayer;
    private int boardSize;

    @FXML private ToggleGroup FirstPlayerTag;
    @FXML private ToggleGroup SecondPlayerTag;
    @FXML private ToggleGroup FirstPlayer;
    @FXML Slider tableSize;

    @FXML private Button doneButton;
    

    @Override
    public void initialize(URL location, ResourceBundle resources) {

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
					 this.forstImagePath = val;
					 this.playerOneTag = new ImageView(getClass().getResource(val).toExternalForm()); 
				 } else if(key.equals("SecondImage")) {
					 this.secondImagePath = val;
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
            this.forstImagePath = "blackTag.png";
            this.secondImagePath = "greyTag.png";
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
    	
    }

    @FXML
    public void saveToFile() {
    	if(this.firstPlayer == 0) {
    		this.firstPlayer = 1;
    	}
		PrintWriter os = null;
		try {
			
			 os = new PrintWriter(new OutputStreamWriter(new FileOutputStream("Settings.txt")));
			 os.println("firstPlayer:" + this.firstPlayer);
			 os.println("firstImage:" + this.forstImagePath);
			 os.println("SecondImage:" + this.secondImagePath);
			 os.println("boardSize:" +(int) this.tableSize.getValue());
			
		} catch(IOException e) {
			
		} finally {
			if( os != null ){ // Exception might have happened at constructor
				os.close();
		}
	}
    }

    @FXML
    public void goBackToMenu() {
        // first save the values
        saveToFile();
        // then go back to menu
        Stage stage = (Stage)this.doneButton.getScene().getWindow();
        try {
            GridPane root = (GridPane) FXMLLoader.load(getClass().getResource("Menu.fxml"));
            Scene scene = new Scene(root, 550, 430);
            stage.setTitle("Menu");
            stage.setScene(scene);
            stage.show();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    @FXML
    public void setPlayerOneTag(ImageView tag){
        this.playerOneTag = tag;
    }
    @FXML
    public void setPlayerTwoTag(ImageView tag){
        this.playerTwoTag = tag;
    }
    /*@FXML
    public void setBoardSize(int boardSize) {
        this.boardSize = boardSize;
    }
    @FXML
    public ImageView getPlayerOneTag() {
        return playerOneTag;
    }
    @FXML
    public ImageView getPlayerTwoTag() {
        return playerTwoTag;
    }
    @FXML
    public int getFirstPlayer() {
        return firstPlayer;
    }
    @FXML
    public double getBoardSize() {
     /*   //if(!tableSize.isValueChanging()){
            return this.tableSize.getValue();
        //}
        // 0;
        //throw new RuntimeException("something Went wrong");
     return 0;
    }*/

    public void setPlayerOneTag(ActionEvent actionEvent) {
        updatePlayerTag(FirstPlayerTag);
    }

    public void setPlayerTwoTag(ActionEvent actionEvent) {
        updatePlayerTag(SecondPlayerTag);
    }

    public void updatePlayerTag(ToggleGroup toggleGroup)
    {
        RadioButton selectedRadioButton = (RadioButton) toggleGroup.getSelectedToggle();
        String selectedToggleID = selectedRadioButton.getId();
        ImageView i = new ImageView();
        switch (selectedToggleID) {
            case "black":
                readAndSetPlayerImage(i, "blackTag.png", PLAYER1);
                break;
            case "blue":
                readAndSetPlayerImage(i, "blueTag.png", PLAYER1);
                break;
            case "green":
                readAndSetPlayerImage(i, "greenTag.png", PLAYER1);
                break;
            case "grey":
                readAndSetPlayerImage(i, "greyTag.png", PLAYER2);
                break;
            case "purple":
                readAndSetPlayerImage(i, "purpleTag.png", PLAYER2);
                break;
            case "red":
                readAndSetPlayerImage(i, "redTag.png", PLAYER2);
                break;
            default:
                throw new RuntimeException("not a legal color");
        }
    }

    private void readAndSetPlayerImage(ImageView i, String colorFilePath, int player) {
        i.setImage(new Image(new File(colorFilePath).toURI().toString()));
        if(player == PLAYER1){
        	this.forstImagePath = colorFilePath;
            setPlayerOneTag(i);
        } else {
        	this.secondImagePath = colorFilePath;
            setPlayerTwoTag(i);
        }
    }

    public void setFirstPlayer(ActionEvent actionEvent) {
        RadioButton selectedRadioButton = (RadioButton) this.FirstPlayer.getSelectedToggle();
        String selectedToggleID = selectedRadioButton.getId();
        if(selectedToggleID.compareTo("player1First")== 0){
            this.firstPlayer = PLAYER1;
        } else {
            this.firstPlayer = PLAYER2;
        }
    }

    /*public void readBoardSize(ActionEvent actionEvent) {
        //int boardSize = (int) this.tableSize.getValue();
        //System.out.println(6);//boardSize
        //setBoardSize((boardSize));
        tableSize.valueProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(
                    ObservableValue<? extends Number> observableValue,
                    Number previous,
                    Number now) {
                if (!tableSize.isValueChanging()) {
                    // This only fires when we're done
                    System.out.println(6);//boardSize
                }
            }
        });

        /*
                                  tableSize.valueProperty().addListener((observable, oldValue, newValue) -> {
                          System.out.println("Slider Value Changed (newValue: " + newValue.intValue() + ")");
                          });

        System.out.println(6);//boardSize
    }*/



}
