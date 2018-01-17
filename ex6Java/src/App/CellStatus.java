package App;

public enum CellStatus {
	E, O, X;
	  /**
	   * Static (class) method. simply utility method.
	   * @param player
	   * @return the other App.Player (if player is X return O etc.)
	   * caution: if the player is E returns E!
	   */
public static CellStatus otherPlayer(CellStatus player) {
	if(player == CellStatus.O) return CellStatus.X;
	if(player == CellStatus.X) return CellStatus.O;
	return CellStatus.E;
}
}
