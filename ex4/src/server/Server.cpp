/*
 * Server.cpp
 *
 *  Created on: 2 בדצמ׳ 2017
 *      Author: yanap
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
		    	}
		   int playerTwo = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		   cout << "Client 2 connected" << endl;
		   if (playerTwo == -1)
			   throw "Error on accept";
		   int second = 2;
		   n = write(playerTwo, &second, sizeof(second));
		   		    if (n == -1) {
		   		    	cout << "Error writing to socket" << endl;
		   		    	return;
		   		    	}
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
	 string massage;
	 while (true) {
	 // Read new point from player.
		 int n = read(player[turnCounter%2], &massage, sizeof(massage));
		 if (n == -1) {
			 cout << "Error reading point" << endl;
			 return;
		 }
		 if (n == 0) {
			 cout << "Client disconnected" << endl;
			 return;
		 }
		 // Write the point back to the other player
		 n = write(player[(turnCounter + 1) % 2], &massage, sizeof(massage));
		 if (n == -1) {
			 cout << "Error writing to socket" << endl;
			 return;
		 }
		 turnCounter++;
		 //if the message is end-return to close connections with players.
		 if (massage == "End") {
			 return;
		 }
	 }
}

