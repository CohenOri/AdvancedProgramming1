import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

public class MenuController {

    @FXML
    private Button startButton;

    @FXML
    private ImageView settings;


    /**
     * start the actual game
     */
    @FXML
    protected void start() {
        Stage stage = (Stage)this.startButton.getScene().getWindow();
        try {
            HBox root = (HBox) FXMLLoader.load(getClass().getResource("Game.fxml"));
            Scene scene = new Scene(root, 550, 430);
            stage.setTitle("Reversi");
            stage.setScene(scene);
            stage.show();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * open settings
     */
    @FXML
    protected void settings() {
        Stage stage = (Stage)this.settings.getScene().getWindow();
        try {
            GridPane root = (GridPane) FXMLLoader.load(getClass().getResource("Settings.fxml"));
            Scene scene = new Scene(root, 550, 430);
            stage.setTitle("Settings");
            stage.setScene(scene);
            stage.show();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}