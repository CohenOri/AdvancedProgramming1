
public interface Player {
		  /**
		   * @return the Slot the player chose to place his tag at
		   */
	public Slot play();
		  /**
		   * @return players symbol as char and not enum.
		   */
	public char getSymbol();
		  /**
		   * input: pointer to board and gameLogic.
		   * output:non
		   * the function make players move-depended what kind of player it is.
		 * @param slot 
		 * @return true or false if move done correctly.
		   */
	public boolean makeAMove(Board b, Logic logic, Slot slot);
	/**
	 * @return enum symbol of player.
	 */
	
	public CellStatus getEnumSymbol();
}
