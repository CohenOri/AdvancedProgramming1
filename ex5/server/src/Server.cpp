/*
 * Server.cpp
 *
 *  Created on: 2 בדצמ׳ 2017
 *      Author: yanap
 */

#include "../include/Server.h"


Server::Server(int port, CheckNewClient checker): port(port), serverSocket(0) {
	this->chkr = checker;
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
		   int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		   cout << "Client 1 connected" << endl;
		   if (clientSocket == -1)
			   throw "Error on accept";

		  // notify that there's new client and save his socket
		  this->chkr.NewClientConnected(clientSocket);

          /* where to put this?!
		   // Close communication with the client
		   close(clientSocket);
		   close(playerTwo);*/

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

