package GUI;

import App.*;
import javafx.fxml.FXMLLoader;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import GUI.*;


public class GameBoardController extends GridPane {

	private Board board;
	private String playerOneTag;
	private String playerTwoTag;
	private ArrayList<Slot> possibleMoves;
/**
 * Constructor.
 * this class control board's printings.
 * @param board param.
 */
	public GameBoardController(Board board) {
		this.possibleMoves = new ArrayList<>();
		this.board = board;
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("GameBoard.fxml"));
		fxmlLoader.setRoot(this);
		fxmlLoader.setController(this);

		try {
			fxmlLoader.load();
		} catch (IOException exception) {
			throw new RuntimeException(exception);
		}
	}
/**
 * draw the board.
 */
	public void draw() {
		this.getChildren().clear();
		int height = (int) this.getPrefHeight();
		int width = (int) this.getPrefWidth();
		int cellHeight = (int) (height / board.getSize());
		int cellWidth = (int) (width / board.getSize());

		// draw slots.
		StackPane stackPane = null;
		Rectangle slot = null;
		Color color[] = { Color.DARKCYAN, Color.DARKKHAKI};
		int tone = 0;//used for change cell's color.
		for (int i = 0; i < board.getSize(); i++) {
			tone++;
			for (int j = 0; j < this.board.getSize(); j++) {
				tone++;
				
				stackPane = new StackPane();
				slot = new Rectangle(cellWidth, cellHeight,   color[tone % 2]);
				//check witch type slot we have and print it.
				switch (this.board.getStatusOfCell(j, i).ordinal()) {
				case 0:// empty
					this.add(slot, j, i);
					break;
				case 1:// X slot
					stackPane.getChildren().add(slot);
					// prints player cell. image we got from the file settings.
					ImageView playerImage =  new ImageView(getClass().getResource(this.playerOneTag).toExternalForm());
					//set image boundaries to place in middle of cell.
					playerImage.setFitHeight(cellHeight);
					playerImage.setFitWidth(cellWidth);
					stackPane.getChildren().add(playerImage);
					this.add(stackPane, j, i);
					break;
				case 2:// O slot
					stackPane.getChildren().add(slot);
					ImageView player2Image = new ImageView(getClass().getResource(this.playerTwoTag).toExternalForm());
					player2Image.setFitHeight(cellHeight);
					player2Image.setFitWidth(cellWidth);
					stackPane.getChildren().add(player2Image);
					this.add(stackPane, j, i);
					break;
				}

			}
		}

		// draw possible slots of current player. note: draw a red circle.
		Iterator<Slot> it = this.possibleMoves.iterator();
		while (it.hasNext()) {
			Slot slot1 = it.next();
			int posX = slot1.GetCol();
			int posY = slot1.GetRow();
			StackPane stackPane1 = new StackPane();
			Circle cell = new Circle(posX, posY,( cellHeight) / 4, Color.FIREBRICK);
			stackPane1.getChildren().add(cell);
			this.add(stackPane1, posY - 1, posX - 1);
		}
	}
/**
 * @return board.
 */
	public Board getBoard() {
		return board;
	}
/**
 * set string of imaged path
 * @param playerOneTag
 */
	public void setPlayerOneTag(String playerOneTag) {
		this.playerOneTag = playerOneTag;
	}
	/**
	 * set string of imaged path
	 * @param playerTwoTag
	 */
	public void setPlayerTwoTag(String playerTwoTag) {
		this.playerTwoTag = playerTwoTag;
	}
/**
 * @param possibleMoves of current player.
 */
	public void setPossibleMoves(ArrayList<Slot> possibleMoves) {
		this.possibleMoves = possibleMoves;
	}

}
