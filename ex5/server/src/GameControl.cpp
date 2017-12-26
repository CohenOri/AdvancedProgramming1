

#include "../include/GameControl.h"
#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>


#include <pthread.h>


// CHANGE IT to UNLIMITED
#define MAX_CONNECTED_CLIENTS 10


using namespace std;

GameControl::GameControl(): listGames(listGames), commandsMap(commandsMap) {

}

GameControl::~GameControl() {
	// TODO Auto-generated destructor stub
}

void GameControl::Run() {
    // list to hold all the client threads
    vector<pthread_t> threads;
    int threadCounter = 0;

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
        cout << "Waiting for clientSocket connections..." << endl;
        // Accept a new clientSocket connection
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Some Client connected" << endl;
        if (clientSocket == -1)
            throw "Error on accept";



        // create new thread and let him handle the client
        // create new struct with all the data the thread need
        struct ClientArgs* cArgs;
        cArgs->clientSocket = clientSocket;
        cArgs->threadArr = threads;
        cArgs->indexAtThreadArr = threadCounter;
        int rc = pthread_create(&threads[threadCounter], NULL, HandleClient, (void *)cArgs);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
        threadCounter++;
        /*//check what command the clientSocket sent and do it
        HandleClient(clientSocket, threads, threadCounter-1);*/



        // Where to do it?!
        // Close communication with the clientSocket
        close(clientSocket);
    }

}


void* GameControl::HandleClient(void *clientArgs) {
    // break the struct back to parameters
    // cast back from void* to struct
    struct ClientArgs* cArgs = (struct ClientArgs*)clientArgs;
    int client = cArgs->clientSocket;
    vector<pthread_t>& refToThreadArr = cArgs->threadArr;
    int indexAtThreadArr = cArgs->indexAtThreadArr;

    // Read massage from player.
    char ma[10];
    char* massage = ma;
    int n = read(client, massage, sizeof(massage));
    if (n == -1) {
        cout << "Error reading point" << endl;
        // remove the thread from threadArr
        refToThreadArr.erase(refToThreadArr.begin()+indexAtThreadArr);
        pthread_exit (NULL); // NULL is to be insert here?!
    } else if (n == 0) {
        cout << "Client disconnected" << endl;
        pthread_exit (NULL); // NULL is to be insert here?!
    }
    if (this->commandsMap.find(massage) != this->commandsMap.end() ) {
        // found the command - execute her
        CommandProtocol* cmdPtr = this->commandsMap[massage];
        cmdPtr->Execute(); // what to insert here?!
    } else {
        // not found
        throw "read Unknown Command from client";
    }
}

