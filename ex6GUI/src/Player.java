
public interface Player {
		  /**
		   * @return the Slot the player chose to place his tag at
		   */
	public Slot Play();
		  /**
		   * @return players symbol as char and not enum.
		   */
	public char GetSymbol();
		  /**
		   * input: pointer to board and gameLogic.
		   * output:non
		   * the function make players move-depended what kind of player it is.
		 * @param slot 
		 * @return 
		   */
	public boolean MakeAMove(Board b, Logic logic, Slot slot);
	/**
	 * @return enum symbol of player.
	 */
	
	public CellStatus GetEnumSymbol();
}
