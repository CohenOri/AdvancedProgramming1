import javafx.fxml.FXMLLoader;
import javafx.scene.control.Cell;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

public class GameBoardController extends GridPane {

    private Board board;
    private ImageView playerOneTag;
    private ImageView playerTwoTag;
    private ArrayList<Slot> possibleMoves;

    public GameBoardController(Board board) {
        this.possibleMoves = new ArrayList<>();
        this.board = board;
        this.playerOneTag.setImage(new Image(new File("blackTag.png").toURI().toString()));
        this.playerTwoTag = new ImageView();
        this.playerTwoTag.setImage(new Image(new File("greyTag.png").toURI().toString()));
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("GameBoard.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
    }


    public void draw() {
        this.getChildren().clear();
        int height = (int)this.getPrefHeight();
        int width = (int)this.getPrefWidth();
        int cellHeight = (int) (height / board.getSize());
        int cellWidth = (int) (width / board.getSize());
        // draw slots
        StackPane stackPane = null;
        Rectangle slot = null;
        
        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < this.board.getSize(); j++) {
            	switch(this.board.GetStatusOfCell(i,j).ordinal()) {
            	case 0://empty
            		slot = new Rectangle(cellWidth, cellHeight, Color.WHITE);
                    slot.setStroke(Color.BLACK);
                    this.add(slot, j, i);
            		break;
            	case 1://X slot
                     stackPane = new StackPane();
                     slot = new Rectangle(cellWidth, cellHeight,  Color.WHITE);
                    slot.setStroke(Color.BLACK);
                    stackPane.getChildren().add(slot);
                    // HOW TO DRAW IMAGEVIEW
                    this.playerOneTag.getImage();
                    stackPane.getChildren().add(the this i draw...);
                    // END OF HOW to draw IMAGEVIEW
                    this.add(stackPane, j, i);
            		break;
            	case 2://O slot
                    stackPane = new StackPane();
                    slot = new Rectangle(cellWidth, cellHeight,  Color.WHITE);
                    slot.setStroke(Color.BLACK);
                    stackPane.getChildren().add(slot);
                    // HOW TO DRAW IMAGEVIEW
                    this.playerTwoTag.getImage();
                    stackPane.getChildren().add(the this i draw...);
                    // END OF HOW to draw IMAGEVIEW
                    this.add(stackPane, j, i);
            		break;
            	}

            }
        }

        // draw possible slots in difreent color
        Iterator<Slot> it = this.possibleMoves.iterator();
        while (it.hasNext()) {
            Slot slot1 = it.next();
            int posX = slot1.GetCol();
            int posY = slot1.GetRow();
            StackPane stackPane1 = new StackPane();
            Rectangle cell = new Rectangle(cellWidth - 1, cellHeight - 1, Color.color(43, 233, 255));
            stackPane1.getChildren().add(slot1);
            this.add(stackPane1, posY, posX);
        }
    }

    public Board getBoard() {
        return board;
    }

    public void setPlayerOneTag(ImageView playerOneTag) {
        this.playerOneTag = playerOneTag;
    }

    public void setPlayerTwoTag(ImageView playerTwoTag) {
        this.playerTwoTag = playerTwoTag;
    }

    public void setPossibleMoves(ArrayList<Slot> possibleMoves) {
        this.possibleMoves = possibleMoves;
    }

}
