package GUI;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;


public class Main extends Application {

    @Override
    /**
     * Starts the game, open menu screen
     */
    public void start(Stage primaryStage) throws Exception{
        GridPane root = (GridPane)FXMLLoader.load(getClass().getResource("Menu.fxml"));
        Scene scene = new Scene(root,300,200);
        primaryStage.setTitle("Menu");
        primaryStage.setScene(scene);
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
