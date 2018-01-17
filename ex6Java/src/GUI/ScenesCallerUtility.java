package GUI;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

// class with methods to call another scenes
public class ScenesCallerUtility {


    private Stage stage;

    /**
     * go to menu Scene when the button is pressed
     * @param pressed
     */
    public void goToMenu(Button pressed){
                Stage stage = (Stage)pressed.getScene().getWindow();
                try {
                    GridPane root = (GridPane) FXMLLoader.load(getClass().getResource("Menu.fxml"));
                    Scene scene = new Scene(root, 300, 200);
                    stage.setTitle("Menu");
                    stage.setScene(scene);
                    stage.show();
                } catch(Exception e) {
                    e.printStackTrace();
                }
        }
}
