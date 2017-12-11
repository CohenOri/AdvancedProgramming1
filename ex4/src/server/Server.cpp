/**
# Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */

#include "Server.h"

Server::Server(int port): port(port), serverSocket(0) {
	cout << "Server" << endl;
}

void Server::start() {
	// Create a socket point
	 serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	 if (serverSocket == -1) {
		 throw "Error opening socket";
	 }
	 // Assign a local address to the socket
	 struct sockaddr_in serverAddress;
	 bzero((void *)&serverAddress, sizeof(serverAddress));
	 serverAddress.sin_family = AF_INET;
	 serverAddress.sin_addr.s_addr = INADDR_ANY;
	 serverAddress.sin_port = htons(port);
	 if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		 throw "Error on binding";
	 }
	 // Start listening to incoming connections
	 listen(serverSocket, MAX_CONNECTED_CLIENTS);
	 // Define the client socket's structures
	  struct sockaddr_in clientAddress;
	  socklen_t clientAddressLen;
	  while (true) {
		   cout << "Waiting for client connections..." << endl;
		   // Accept a new client connection
		   int playerOne = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		   cout << "Client 1 connected" << endl;
		   if (playerOne == -1)
			   throw "Error on accept";
		   int first = 1;
		   //send to the first client-that he is the first.
		   int n = write(playerOne, &first, sizeof(first));
		    if (n == -1) {
		    		cout << "Error writing to socket" << endl;
		    		return;
		    	} else if (n == 0) {
				 cout << "Client disconnected" << endl;
				 return;
			 }
		    //connect another client
		   int playerTwo = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		   cout << "Client 2 connected" << endl;
		   if (playerTwo == -1)
			   throw "Error on accept";
		   int second = 2;
		   //send him he is the second.
		   n = write(playerTwo, &second, sizeof(second));
		   if (n == -1) {
		   	cout << "Error writing to socket" << endl;
		   	return;
		   	} else if (n == 0) {
				 cout << "Client disconnected" << endl;
				 return;
			 }
		   //send to the first player that he can sarts the game.
		  int m = write(playerOne, &second, sizeof(second));
		   if (m == -1) {
		 		   	cout << "Error writing to socket" << endl;
			    	return;
		 	} else if (n == 0) {
				 cout << "Client disconnected" << endl;
				 return;
			 }
		   //start the game.
		   handleClient(playerOne, playerTwo);
		   // Close communication with the client
		   close(playerOne);
		   close(playerTwo);
	  }
}

void Server::stop() {
	 close(serverSocket);
}

Server::~Server() {
}

void Server::handleClient(int playerX, int playerO) {
	int player[] =  { playerX, playerO };
	int turnCounter = 0;
	 char ma[10];
	 char* massage = ma;
	 while (true) {
		 memset(ma,0,10);//empty the values.
	 // Read massage from player.
		 int n = read(player[turnCounter%2], massage, sizeof(massage));
		 if (n == -1) {
			 cout << "Error reading point" << endl;
			 return;
		 } else if (n == 0) {
			 cout << "Client disconnected" << endl;
			 return;
		 }
		 // Write the massage back to the other player
		 n = write(player[(turnCounter + 1) % 2], massage, sizeof(massage));
		 if (n == -1) {
			 cout << "Error writing to socket" << endl;
			 return;
		 } else if (n == 0) {
					 cout << "Client disconnected" << endl;
					 return;
		}
		 turnCounter++;
		 //if the message is end-return to close connections with players.
		if (strcmp(massage,"End") == 0) {
			 return;
		 }
	 }
}

