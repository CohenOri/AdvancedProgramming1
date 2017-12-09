/*
 * HostPlayer.cpp
 *
 *  Created on: 2 בדצמ׳ 2017
 *      Author: yanap
 */

#include "../include/HostPlayer.h"


HostPlayer::HostPlayer(const char* serverIP, int serverPort) :serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
 cout << "Client" << endl;
}

void HostPlayer::connectToServer() {
	 // Create a socket point
	 clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	 if (clientSocket == -1) {
		 throw "Error opening socket";
	 }
	 // Convert the ip string to a network address
	 struct in_addr address;
	 if (!inet_aton(serverIP, &address)) {
		 throw "Can't parse IP address";
	 }
	 // Get a hostent structure for the given host address
	 struct hostent *server;
	 server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);
	 if (server == NULL) {
		 throw "Host is unreachable";
	 }
	 // Create a structure for the server address
	 struct sockaddr_in serverAddress;
	 bzero((char *)&address, sizeof(address));
	 serverAddress.sin_family = AF_INET;
	 memcpy((char *)&serverAddress.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
	 // htons converts values between host and network byte orders
	 serverAddress.sin_port = htons(serverPort);
	 	// Establish a connection with the TCP server
	 if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		 throw "Error connecting to server";
	 }
	 cout << "Connected to server" << endl;
}

void HostPlayer::getSymbolFromServer() {
	int player;
	int start;
	//read which player are you
	int n = read(clientSocket, &player, sizeof(player));
	if (n == -1) {
		throw "Error reading result from socket";
	}
		if (player == 1) {
			this->player = EnumDeclration::X;
			this->symbol = 'X';
			cout << "waiting for other player to conect.." << endl;
			int n = read(clientSocket, &start, sizeof(start));
			if (n == -1) {
					throw "Error reading result from socket";
			}
			this->firstMove = true;
		} else {
			this->player = EnumDeclration::O;
			this->symbol = 'O';
			this->firstMove = true;
		}
		cout << "you are: " << this->symbol << endl;
}

Slot HostPlayer::Play() {
	/*  string str;
	  cout << "\n\n" << "Please enter your row,col: ";
	  getline(cin, str);

	  try {
	    return Slot(str, this->player);
	  }
	  catch (exception exception) {
	    cout << "Are you serious? enter something in the row, col format!";
	    return Play();
	  }*/
}

char HostPlayer::GetSymbol() { return this->symbol; }

void HostPlayer::MakeAMove(Board* b, LogicInterface* logic) {
	bool stop = false;//refrence if we need to stop the connection.
//	if(this->GetSymbol() == 'X') {firstMove = true; }//player x always starts.
	//print begginig board.
	//b->Print();
	//if its other players first move-just get their answer.
	//else-first send yours.
	if(b->GetLastMove().compare("End") == 0) {
		sendMove("End");
		return;
	}
	 if(firstMove) {
		 if(!(this->player == EnumDeclration::O)) {
			 this->firstMove = false;
			 return;
		 }
	}
	if(!firstMove) sendMove(b->GetLastMove());
	this->firstMove = false;
	char buffer[10];
	char *p = buffer;
	int n = read(clientSocket, p, sizeof(p));
	if (n == -1) {
		throw "Error reading result from socket";
	}
	string answer(buffer);
	cout << "this is what received: " << answer << endl;
	if (answer.compare("End") == 0) {
		//end of the game-we can stop.
		b->SetLastMove("End");
		//if NoMove means other player have no moves
	} else if (answer.compare("NoMove") == 0) {
		b->SetLastMove("NoMove");
		return;//to get new moves
	} else {
		reciveMove(b, logic,Slot(answer, this->player));

	}
}

	//if enemy first


/*	while (!stop) {
		//if its the first move-just get move from player and send.
		if(firstMove) {
			firstMove = false;
			try {
				placeSlotOfPlayer(b, logic);
				b->Print();
			} catch (const char *msg) {
				cout << msg << endl;
				return;
			}
		} else {//if its not the first move.
			char buf[10];
			char* s = buf;
			//get other player move.
			int n = read(clientSocket, s, sizeof(s));
			if (n == -1) {
				throw "Error reading result from socket";
			}
			string result(s);
			cout << "this is what received: " << result << endl;
			//if we received end-means end of game-return back to gameFlow.
			if (result.compare("End") == 0) {
				stop = true;
				return;
			//if NoMove means other player have no moves
			} else if (result.compare("NoMove") == 0) {
				try {
					stop = placeSlotOfPlayer(b, logic);
					b->Print();
				} catch (const char *msg) {
					cout << msg << endl;
					return;
				}
			//players move is correct.
			} else {
				try {
					//place enemys slot on the board.
					reciveMove(b, logic, Slot(result, EnumDeclration::OtherPlayer((this->player))));
					//make a turn.
				stop =	placeSlotOfPlayer(b, logic);
					b->Print();
				} catch (const char *msg) {
					cout << msg << endl;
					return;
				}
			}

	 }
	}*/


void HostPlayer::reciveMove(Board* b, LogicInterface* logic, Slot move) {
	//place other player move on board and print new board.
	  b->SetCellStatus(move.GetRow(), move.GetCol(),  EnumDeclration::OtherPlayer((this->player)));
	  logic->FlipSlots(move.GetRow(), move.GetCol(),  EnumDeclration::OtherPlayer((this->player)));
		b->Print();
}

void HostPlayer::sendMove(string move) {
	cout << "start send move:" << endl;
	cout << move << endl;
	int n = write(clientSocket, move.c_str(), sizeof(move.c_str()));
	if (n == -1) {
		throw "Error reading result from socket";
	}
	cout << "end of send/" << endl;
}

bool HostPlayer::placeSlotOfPlayer(Board* b, LogicInterface* logic) {
   /* if (logic->SlotsToPlace(this->player).size() == 0) {
    		if (logic->SlotsToPlace( EnumDeclration::OtherPlayer((this->player))).size() == 0) {
        		sendMove("End");
    			return true;
    		}
    		cout << "no moves for you" << endl;
    		sendMove("NoMove");
    		return false;
    }
	  cout << this->GetSymbol() << " I'ts your move.\n" << "Your possible moves: ";
	  vector<Slot> v = logic->SlotsToPlace(this->player);
	  for (unsigned int i = 0; i < v.size(); i++) {
	    v[i].Print();
	  }
	  // get the chosen slot from the player, confirm its legal slot and add it to the board_.
	  Slot chosenSlot = Play();
	  cout << "this is your choice: ";
	  chosenSlot.Print();
	  cout << chosenSlot.GetCellStatus();
	  cout << endl;

	  //check if choice is correct-if not ask again.
	  if (chosenSlot.ExistInVector(logic->SlotsToPlace(this->player))) {
	    b->SetCellStatus(chosenSlot.GetRow(), chosenSlot.GetCol(), this->player);
	    logic->FlipSlots(chosenSlot.GetRow(), chosenSlot.GetCol(), this->player);
	    sendMove(chosenSlot.GetString());
	    if ((logic->SlotsToPlace(this->player).size() == 0) &&
	    		(logic->SlotsToPlace( EnumDeclration::OtherPlayer((this->player))).size() == 0)) {
		    //sendMove("End");
		    //return true;
	    }
	    return false;
	  } else {
	    cout << "ILLEGAL PLACE FOR TAG " << GetSymbol() << " try again" << endl;
	    return placeSlotOfPlayer(b, logic);
	  }*/
}

EnumDeclration::CellStatus HostPlayer::getEnumSymbol() { return EnumDeclration::OtherPlayer((this->player)); }

