
public class GameFlow {
	
	private  Logic logic;
	private	 Board board;
	private	 Player player[];
	private  CellStatus currentTurn;
	private int turnCounter;
	private GUI drawer;
			/**
			 * Class that holds all the information in order to run the game
			 * @param logic - logic the game run with
			 * @param board - game board
			 * @param player1
			 * @param player2
			 * @param drawer 
			 */
	public  GameFlow(Logic logic, Board board, Player player1, Player player2, GUI drawer) {
	    this.logic = logic;
	    this.board = board;
	    this.turnCounter = 0;
	    //this.currentTurn = CellStatus.X;
	    this.player = new Player[2];
	    this.player[0] = player1;
	    this.player[1] = player2;
	    this.drawer = drawer;
	    // some initialization
	    board.SetCellStatus(board.NumOfRows() / 2, board.NumOfCols() / 2, CellStatus.O);
	    board.SetCellStatus(board.NumOfRows() / 2 + 1, board.NumOfCols() / 2 + 1, CellStatus.O);
	    board.SetCellStatus(board.NumOfRows() / 2 + 1, board.NumOfCols() / 2, CellStatus.X);
	    board.SetCellStatus(board.NumOfRows() / 2, board.NumOfCols() / 2 + 1, CellStatus.X);
	}
		  /**
		   * Run the game
		   */
	public	  void Run() {
	/*	  Board b = this.board;
		  int tunrnConter = 0;
		  b.Print();
		  // run the game while it is still not over
		  while (!GameOver()) {
			  //check who's turn it is.
			  System.out.print("here3\n");
			  if(tunrnConter%2 == 1) {
				  this.currentTurn = CellStatus.O;
			  } else {
				  this.currentTurn = CellStatus.X;
			  }
		      // if player has possible slots to place.
		   if (this.logic.SlotsToPlace(this.currentTurn).size() != 0) {
		       // player makes a move.
		     this.player[tunrnConter % 2].MakeAMove(this.board, this.logic);
		   } else {
		        // it doesn't have possible slots to place tag at
		        // the turn passes over
			   System.out.print(player[tunrnConter % 2].GetSymbol() +
		              " I'ts your move. but unfortunately you don't have anything to do," +
		             "therefore it's only fair that the play passes back to other player"
		             );
		      }
		   tunrnConter++;
		   this.board.Print();//print the board.
		  }
		  System.out.print("here3\n");
		  //print end game screen.
		  EndGame();**/
	}
		  /**
		   * @return if Game is Over
		   */
	public	  boolean GameOver() {
		  if (this.logic.SlotsToPlace(CellStatus.X).size() != 0
			      || this.logic.SlotsToPlace(CellStatus.O).size() != 0) {
			    return false;
			  }
			  return true;
	}
		  /**
		   * return who is the winner by string.
		   */
	public  String EndGame() {
		  Board b = this.board;
		    // declare result
		    if (b.GetXSlots().size() > b.GetOSlots().size()) {
		    	return "Player 1";
		    } else if (b.GetXSlots().size() < b.GetOSlots().size()) {
		    	return "player 2";
		    } else {
		    	return "It's a TIE!";
		    }
	}
	/**
	 * play players turn. if slot illigal-return false and don't change the turn;
	 * @param slot
	 * @return
	 */
		public boolean playOneTurn(Slot slot) {
			 
			boolean correctMove = this.player[this.turnCounter % 2].MakeAMove(this.board, this.logic, slot);
			if(correctMove) this.turnCounter++;
			if(this.logic.SlotsToPlace(this.player[this.turnCounter % 2].GetEnumSymbol()).size() == 0) this.drawer.drawMessage("next!");
			this.drawer.drawPossibleMovesTitle(this.logic.SlotsToPlace(this.player[this.turnCounter % 2].GetEnumSymbol()));
			this.drawer.SetPlayer(this.player[(this.turnCounter ) % 2].GetEnumSymbol());
			this.drawer.drawGame();
			return correctMove;
		}
		/**
		 * @return board.
		 */
		public Board GetBoard() {
			return this.board;
		}
}
