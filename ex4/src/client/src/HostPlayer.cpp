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
		int n = read(clientSocket, &player, sizeof(player));
		if (n == -1) {
			throw "Error reading result from socket";
		}
		if (player == 1) {
			this->player = EnumDeclration::X;
			this->symbol = 'X';
		} else {
			this->player = EnumDeclration::O;
			this->symbol = 'O';
		}
		cout << "you are: " << player << endl;
}

Slot HostPlayer::Play() {
	  int row;
	  int col;
	  int i;
	  string str;
	  vector<int> vect;
	  cout << "\n\n" << "Please enter your row,col: ";
	  getline(cin, str);
	  stringstream ss(str);
	  while (ss >> i) {
	    vect.push_back(i);

	    if (ss.peek() == ',')
	      ss.ignore();
	  }
	  try {
	    return Slot(vect.at(0), vect.at(1));
	  }
	  catch (exception exception) {
	    cout << "Are you serious? enter something in the row, col format!";
	    return Play();
	  }
}

char HostPlayer::GetSymbol() { return this->symbol; }

void HostPlayer::MakeAMove(Board* b, LogicInterface* logic) {
	 bool stop = false;
	 bool firstMove = false;
	 if(this->GetSymbol() == 'X') { firstMove = true; }
	while (!stop) {
		b->Print();
		if(firstMove) {
			firstMove = false;
			try {
			placeSlotOfPlayer(b, logic);
			} catch (const char *msg) {
				cout << msg << endl;
				return;
			}
		} else {
			string result;
			int n = read(clientSocket, &result, sizeof(result));
			if (n == -1) {
				throw "Error reading result from socket";
			}
			if (result == "End") {
				stop = true;
			} else if (result == "“NoMove”") {
				try {
					stop = placeSlotOfPlayer(b, logic);
				} catch (const char *msg) {
					cout << msg << endl;
					return;
				}
			} else {
				try {
					reciveMove(b, logic, result);
					stop = placeSlotOfPlayer(b, logic);
				} catch (const char *msg) {
					cout << msg << endl;
					return;
				}
			}


	 }
	}
}

void HostPlayer::reciveMove(Board* b, LogicInterface* logic, string move) {
	  vector<int> vect;
	  int i;
	  stringstream ss(move);
	  while (ss >> i) {
	    vect.push_back(i);
	    if (ss.peek() == ',')
	      ss.ignore();
	  }
	  Slot enemy = Slot(vect.at(0), vect.at(1), EnumDeclration::OtherPlayer((this->player)));
	  b->SetCellStatus(enemy.GetRow(), enemy.GetCol(),  EnumDeclration::OtherPlayer((this->player)));
	  logic->FlipSlots(enemy.GetRow(), enemy.GetCol(),  EnumDeclration::OtherPlayer((this->player)));
}

void HostPlayer::sendMove(string move) {
	int n = write(clientSocket, &move, sizeof(move));
	if (n == -1) {
		throw "Error writing op to socket";
	}
}

bool HostPlayer::placeSlotOfPlayer(Board* b, LogicInterface* logic) {
    if (logic->SlotsToPlace(this->player).size() == 0) {
    		if (logic->SlotsToPlace( EnumDeclration::OtherPlayer((this->player))).size() == 0) {
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
	  if (chosenSlot.ExistInVector(logic->SlotsToPlace(this->player))) {
	    b->SetCellStatus(chosenSlot.GetRow(), chosenSlot.GetCol(), this->player);
	    logic->FlipSlots(chosenSlot.GetRow(), chosenSlot.GetCol(), this->player);
	    sendMove(chosenSlot.getString());
	    if ((logic->SlotsToPlace(this->player).size() == 0) &&
	    		(logic->SlotsToPlace( EnumDeclration::OtherPlayer((this->player))).size() == 0)) {
		    sendMove("End");
		    return true;
	    }
	    return false;
	  } else {
	    cout << "ILLEGAL PLACE FOR TAG " << GetSymbol() << " try again" << endl;
	    return placeSlotOfPlayer(b, logic);
	  }
}
