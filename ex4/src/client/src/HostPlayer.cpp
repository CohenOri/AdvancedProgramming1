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
	this->firstMove = true;
	//read which player are you
	int n = read(clientSocket, &player, sizeof(player));
	if (n == -1) {
		throw "Error reading result from socket";
	}//if you 1 mean you are X.
	if (player == 1) {
		this->player = EnumDeclration::X;
		//symbol type here referees to enemy.
		this->symbol = 'O';
		//other player connect when we receive num2 from server.
		cout << "waiting for other player to connect.." << endl;
		int n = read(clientSocket, &start, sizeof(start));
		if (n == -1) {
			throw "Error reading result from socket";
		}
		//print to player who is he.
		cout << "you are: X" << endl;
	} else {//if player is 2-he is second.
		this->player = EnumDeclration::O;
		this->symbol = 'X';
		//print to player who is he.
		cout << "you are: O" << endl;
		}
}

Slot HostPlayer::Play() { return Slot(-1,-1); }

char HostPlayer::GetSymbol() { return this->symbol; }

void HostPlayer::MakeAMove(Board* b, LogicInterface* logic) {
	//first if we End the game-just send end and return.
	if(b->GetLastMove().compare("End") == 0) {
		SendMove("End");
		return;
		//if its the first move-check if the plyer is X
		//if X return to get from TerminalPlayer a move.
	} else if(firstMove) {
		 if(!(this->player == EnumDeclration::O)) {
			 this->firstMove = false;
			 return;
		 }
		 //if its not first move-send players move to server.
	} else if(!firstMove) SendMove(b->GetLastMove());
	this->firstMove = false;
	//instalize buffer. read from server array.
	char buffer[10]= {0};
	cout << "Waiting for other player's move..." << endl;
	int n = read(clientSocket, buffer, sizeof(buffer));
	if (n == -1) {
		throw "Error reading result from socket";
	}
	//create a string from the array.
	string answer(buffer);
	//if we got End-finish the game.
	if (answer.compare("End") == 0) {
		//update boards last move.
		b->SetLastMove("End");
		//if NoMove means other player have no moves
	} else if (answer.compare("NoMove") == 0) {
		b->SetLastMove("NoMove");
		cout << "Enemy has no moves-turn goes back to you." << endl;
		return;//to get new moves

		//we assume that any other move is int, int
	} else {
		ReciveMove(b, logic,Slot(answer, this->player));

	}
}

void HostPlayer::ReciveMove(Board* b, LogicInterface* logic, Slot move) {
	//place other player move on board and print new board.
	  b->SetCellStatus(move.GetRow(), move.GetCol(),  EnumDeclration::OtherPlayer((this->player)));
	  logic->FlipSlots(move.GetRow(), move.GetCol(),  EnumDeclration::OtherPlayer((this->player)));
	  //print updated board for player.
	  cout <<  this->symbol <<" played: ";
	  move.Print();
	  cout << endl;
		b->Print();
}

void HostPlayer::SendMove(string move) {
	//instelize the buffer array and copy the string.
	char buf[10] = {0};
	size_t length = move.copy(buf,move.size(),0);
	buf[length]='\0';
	//send the buffer.
	int n = write(clientSocket, buf, strlen(buf));
	if (n == -1) {
		throw "Error reading result from socket";
	}
}

EnumDeclration::CellStatus HostPlayer::getEnumSymbol() { return EnumDeclration::OtherPlayer((this->player)); }

