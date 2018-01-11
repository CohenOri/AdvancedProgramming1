
public class main {
	  // initialize new board_, create the objects requried for
	  // game flow to run and run it.
	int main() {
	  Board b = new Board(4, 4);
	  RegularLogic rl = new RegularLogic(b);
	  Player p1 = new TerminalPlayer(CellStatus.X);
	  Player p2 = new TerminalPlayer(CellStatus.O);
	  GameFlow gameFlow = new GameFlow(rl, b, p1, p2);
	  gameFlow.Run();
	return 0;
	}
}
