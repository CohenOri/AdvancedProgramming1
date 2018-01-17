import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Slider;
import javafx.scene.control.ToggleGroup;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.URL;
import java.util.ResourceBundle;

public class SettingsController implements Initializable {

    private static final int PLAYER1 = 1;
    private static final int PLAYER2 = 2;

    private ImageView playerOneTag;
    private ImageView playerTwoTag;
    private String firstImagePath;
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
        /** in case I wanted to show the user default setting in the radio buttons I could set here their values
         * but I believe it nicer without that since I want to make sure he chooses all of them.
         */
    }

    /**
     * save the settings to file
     */
    @FXML
    public void saveToFile() {
    	if(this.firstPlayer == 0) {
    		this.firstPlayer = 1;
    	}
    	//create a buffer.
		PrintWriter os = null;
		try {
			//write all paramters.
			 os =  new PrintWriter("Settings.txt", "UTF-8");
			 os.println("firstPlayer:" + this.firstPlayer);
			 os.println("firstImage:" + this.firstImagePath);
			 os.println("SecondImage:" + this.secondImagePath);
			 os.println("boardSize:" +(int) this.tableSize.getValue());
			
		} catch(IOException e) {
			
		} finally {
			if( os != null ){ // Exception might have happened at constructor
				os.close();
		}
	}
    }

    /**
     * go back to menu scene when pressed done button
     */
    @FXML
    public void goBackToMenu() {
        // first save the values
        saveToFile();
        // go back to menu
        ScenesCallerUtility scu = new ScenesCallerUtility();
        scu.goToMenu(this.doneButton);
        // then go back to menu
    }

    /**
     *
     * @param tag image to set
     */
    @FXML
    public void setPlayerOneTag(ImageView tag){
        this.playerOneTag = tag;
    }

    /**
     * image to set
     * @param tag
     */
    @FXML
    public void setPlayerTwoTag(ImageView tag){
        this.playerTwoTag = tag;
    }

/**
 * @param actionEvent to update player.
 */
    public void setPlayerOneTag(ActionEvent actionEvent) {
        updatePlayerTag(FirstPlayerTag);
    }
/**
 * @param actionEvent
 */
    public void setPlayerTwoTag(ActionEvent actionEvent) {
        updatePlayerTag(SecondPlayerTag);
    }
/**
 * @param toggleGroup to check what option user chose.
 */
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
/**
 * read and set images of users choice via settings
 * @param i
 * @param colorFilePath
 * @param player
 */
    private void readAndSetPlayerImage(ImageView i, String colorFilePath, int player) {
        i.setImage(new Image(new File(colorFilePath).toURI().toString()));
        if(player == PLAYER1){
        	this.firstImagePath = colorFilePath;
            setPlayerOneTag(i);
        } else {
        	this.secondImagePath = colorFilePath;
            setPlayerTwoTag(i);
        }
    }
/**
 * @param actionEvent read first player from button.
 */
    public void setFirstPlayer(ActionEvent actionEvent) {
        RadioButton selectedRadioButton = (RadioButton) this.FirstPlayer.getSelectedToggle();
        String selectedToggleID = selectedRadioButton.getId();
        if(selectedToggleID.compareTo("player1First")== 0){
            this.firstPlayer = PLAYER1;
        } else {
            this.firstPlayer = PLAYER2;
        }
    }
}
