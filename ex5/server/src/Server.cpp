/*
 * Server.cpp
 *
 *  Created on: 2 בדצמ׳ 2017
 *      Author: yanap
 *      11
 */

#include "../include/Server.h"
#define THREADS_NUM 10

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
	/**  struct sockaddr_in clientAddress;
	  socklen_t clientAddressLen;
	  pthread_t threads[THREADS_NUM];

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

	  }**/
}

void Server::stop() {
	 close(serverSocket);
}

Server::~Server() {

}

void Server::handleClient(int playerX, int playerO) {
	/**
	 * not rellevnt for now.
	 *
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
	 }***/
}

int Server::ConnectNewClients() {
	  struct sockaddr_in clientAddress;
	  socklen_t clientAddressLen;

	   int player = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
	   cout << "Client 1 connected" << endl;
	   if (player == -1)
		   throw "Error on accept";
	   return player;
}

void Server::CloseClientSocket(int player) {
	//close clients socket.
	close(player);
}

void Server::SendMessageToClient(int player, char* massage) {
	int n = write(player, massage, sizeof(massage));
	 if (n == -1) {
		 cout << "Error writing to socket" << endl;
		 return;
	 } else if (n == 0) {
		  cout << "Client disconnected" << endl;
	    return;
	}
}

char* Server::GetMessageFromClient(int player) {
	char massage[50];
	char* buffer = massage;
	//read from client massage.
	 int n = read(player, buffer, sizeof(buffer));
	 //if reading didnt work-return null/
	 if (n == -1) {
		 cout << "Error reading point" << endl;
		 return NULL;
		 //if client dosconnected-return null
	 } else if (n == 0) {
		 cout << "Client disconnected" << endl;
		 return NULL;
	 }
	 //return massage from client.
	 return buffer;
}
