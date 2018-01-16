
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.scene.layout.HBox;


public class Main extends Application {

    @Override
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
