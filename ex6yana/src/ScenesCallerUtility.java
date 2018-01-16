import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

// class with static methods to call another scene
public class ScenesCallerUtility {


    private Stage stage;

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
            /*case "Game":
                stage = (Stage)pressed.getScene().getWindow();
                try {
                    HBox root = (HBox) FXMLLoader.load(FXMLLoader.class.getResource("Game.fxml"));
                    Scene scene = new Scene(root, 550, 430);
                    stage.setTitle("Reversi");
                    stage.setScene(scene);
                    stage.show();
                } catch(Exception e) {
                    e.printStackTrace();
                }*/
        }

}
