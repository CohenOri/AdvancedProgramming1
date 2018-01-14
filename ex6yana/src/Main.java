import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class Main {
	  // initialize new board_, create the objects requried for
	  // game flow to run and run it.
	public static void main(String[] args) {
	  Board b = new Board(4, 4);
	  Logic rl = new Regular(b);
	  Player p1 = null;
	  Player p2 = null;
		BufferedReader is = null;
		try {
			is = new BufferedReader(new InputStreamReader(new FileInputStream(" someFile . txt ")));
					String line ;
					 while ((line = is.readLine()) != null ) { // ’null ’->no more data in the stream
					 String[] parts = line.split(":");
					 String key = parts[0];//configurations.
					 String val = parts[1];//the data user instert.
					 if (key.equals("firstPlayer")) {
						 //if first player is 1 means x starts.
						 if(Integer.parseInt(val) == 1) {
							   p1 = new TerminalPlayer(CellStatus.X);
							   p2 = new TerminalPlayer(CellStatus.O);
						 } else { //means o start.
							   p1 = new TerminalPlayer(CellStatus.O);
							   p2 = new TerminalPlayer(CellStatus.X);
						 }
					 } else if(key.equals("firstImage:")) {
					 		b.SetPlayerImage(val, 1);
					 } else if(key.equals("SecondImage")) {
					 		b.SetPlayerImage(val, 2);
					 } else if(key.equals("boardSize")) {
						 //set boards size.
						 b.SetSize(Integer.parseInt(val), Integer.parseInt(val));
					 }
					 }
					  GameFlow gameFlow = new GameFlow(rl, b, p1, p2);
					  gameFlow.Run();
			
	} catch( IOException e) {
		System.out.print("There was some problem\n");

	} finally {
		if( is != null ){ // Exception might have happened at constructor
			try {
				is.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
	}
	}
	}
	
	
	public void writeing() {
		PrintWriter os = null;
		int first = 0, size = 0;
		String path1 = null, path2 = null;
		try {
			 os = new PrintWriter(new OutputStreamWriter(new FileOutputStream(" someFile . txt ")));
			 os.write("firstPlayer:" + first);
			 os.println("firstImage:" + path1);
			 os.println("secindImage:" + path2);
			 os.println("boardSize:" + size);
			
		} catch(IOException e) {
			
		} finally {
			if( os != null ){ // Exception might have happened at constructor
				os.close();
		}
	}

	}
}