
public class GameFlow {
	
	private  Logic logic;
	private	  Board board;
	private	  Player player[];
	private    CellStatus currentTurn;
			/**
			 * Class that holds all the information in order to run the game
			 * @param logic - logic the game run with
			 * @param board - game board
			 * @param player1
			 * @param player2
			 */
	public  GameFlow(Logic logic, Board board, Player player1, Player player2) {
	    this.logic = logic;
	    this.board = board;
	    this.currentTurn = CellStatus.X;
	    this.player = new Player[2];
	    this.player[0] = player1;
	    this.player[1] = player2;
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
		  Board b = this.board;
		  int tunrnConter = 0;
		  b.Print();
		  // run the game while it is still not over
		  while (!GameOver()) {
			  //check who's turn it is.
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
		  //print end game screen.
		  EndGame();
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
		   * prints why the game end and who is the winner
		   */
	public  void EndGame() {
		  Board b = this.board;

		    int num_of_slots_in_board = b.NumOfRows() * b.NumOfCols();
		    int num_of_used_slots = b.GetXSlots().size() + b.GetOSlots().size();
		    if (num_of_used_slots >= num_of_slots_in_board) {
		    	System.out.print("Game is over, board is completely full\n");
		    } else {
		    	System.out.print("Game is over, both sides can't make any more moves\n");
		    }
		    // declare result
		    if (b.GetXSlots().size() > b.GetOSlots().size()) {
		    	System.out.print( "X is the WINNER!\n");
		    } else if (b.GetXSlots().size() < b.GetOSlots().size()) {
		    	System.out.print("O is the WINNER!\n");
		    } else {
		    	System.out.print( "It's a tie\n");
		    }
	}
}
