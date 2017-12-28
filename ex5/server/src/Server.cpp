/*
 * Server.cpp
 *
 *  Created on: 2 בדצמ׳ 2017
 *      Author: yanap
 */

#include "../include/Server.h"
#define THREADS_NUM 10

Server::Server(int port, GameControl* controller): port(port), serverSocket(0) {
	this->controller = controller;
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
	 struct sockaddr_in clientAddress;
	 socklen_t clientAddressLen;
	 int threadCounter = 0;

	 pthread_t end;
	 struct ClientArgs* arg;
	 arg->clientSocket = 0;
	 arg->indexAtThreadArr = 0;
	 arg->controller = this->controller;

	 int rc = pthread_create(&end, NULL, closeAllGames, (void *)arg);
	 if (rc) {
				   cout << "Error: unable to create thread, " << rc << endl;
	   	    	 return;
	 }
	 while (true) {
		   cout << "Waiting for client connections..." << endl;
		   // Accept a new client connection
		   int playerNumber = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		   cout << "Client " <<  playerNumber << " connected" << endl;

		   struct ClientArgs* cArgs;
		   cArgs->clientSocket = playerNumber;
		   cArgs->controller = this->controller;
		   cArgs->indexAtThreadArr = threadCounter;
		   int rc = pthread_create(&threads.at(threadCounter), NULL, HandleClient, (void *)cArgs);
		   if (rc) {
			   cout << "Error: unable to create thread, " << rc << endl;
   	    	 return;
		   }
		   threadCounter++;
   	 }

	 }

void Server::stop() {
	 close(serverSocket);
}

Server::~Server() {

}

void Server::handleClient(int playerX, int playerO) {
//not relevent
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
		 //if client disconnected-return null
	 } else if (n == 0) {
		 cout << "Client disconnected" << endl;
		 return NULL;
	 }
	 //return massage from client.
	 return buffer;
}


void* HandleClient(void *clientArgs) {
    // break the struct back to parameters
    // cast back from void* to struct
    struct ClientArgs* playersInfo = (struct ClientArgs*)clientArgs;
    int client = playersInfo->clientSocket;
    vector<pthread_t>& refToThreadArr = playersInfo->threadArr;
    int indexAtThreadArr = playersInfo->indexAtThreadArr;
    GameControl* control = playersInfo->controller;
    // Read massage from player.
    char ma[50];
    char* buffer = ma;
    bool endReading = false;
    do {
    int n = read(client, buffer, sizeof(buffer));
    if (n == -1) {
        cout << "Error reading point" << endl;
        // remove the thread from threadArr
        refToThreadArr.erase(refToThreadArr.begin()+indexAtThreadArr);
        pthread_exit (NULL); // NULL is to be insert here?!
    } else if (n == 0) {
        cout << "Client disconnected" << endl;
        pthread_exit (NULL); // NULL is to be insert here?!
        }
    //concert array to string.
    string massage(buffer);
    //split the massage to the command and valus clients send.
    //value will be name.
	  string i;
	  vector<string> vect;
	  stringstream ss(massage);
	  while (ss >> i) {
	    vect.push_back(i);
	   if (ss.peek() == ' ')
	      ss.ignore();
	  }
	  string command = vect.at(0);
	  string val = vect.at(1);

	  //create struct of rguments command will get.
	  CommandInfo args;
	  args.clientSocket = client;
	  args.gameName = val;
	  if(!control->executeCommand(command, args)) {
		  endReading = true;
	  }


    } while(!endReading);
}

void* closeAllGames(void *args) {
    struct ClientArgs* playersInfo = (struct ClientArgs*)args;
    GameControl* control = playersInfo->controller;
    string checkToclose;
    bool stop = false;
    while(!stop) {
     cin >> checkToclose;
     if (checkToclose.compare("exit")) {
    	 stop = true;
    	 control->End();
    	 pthread_exit(NULL);
     }
    }
}
