

#include "../include/GameControl.h"
/*#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>*/


#include <pthread.h>


// CHANGE IT to UNLIMITED
#define MAX_CONNECTED_CLIENTS 10


using namespace std;

GameControl::GameControl(int port): port(port), chkr(CheckNewClient()), server(Server(port, this->chkr)) {
    //this->port = port;
    //this->chkr = CheckNewClient();
    //server = Server(port, this->chkr);

    // ListGames and CommandMAP ?!

}

GameControl::~GameControl() {
	// TODO Auto-generated destructor stub
}

void GameControl::Run() {
    // start running the server
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }

    // list to hold all the client threads
    vector<pthread_t> threads;
    int threadCounter = 0;

    while (true) {
        if(this->chkr.CheckIfNewClientConnected()){
            // read the client once
            int clientSocket = this->chkr.ReturnClientSocket();
            this->chkr.ClientHasBeenRead();

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
            HandleClient(clientSocket, threads, threadCounter-1); GARBAGE*/



            /* Where to do it?!
            // Close communication with the clientSocket
            close(clientSocket); */
        }
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
        // remove the thread from threadArr
        refToThreadArr.erase(refToThreadArr.begin()+indexAtThreadArr);
        pthread_exit (NULL); // NULL is to be insert here?!
    }
    // try to find and execute the command
    if (this->commandsMap.find(massage) != this->commandsMap.end() ) {
        // found the command - execute her
        CommandProtocol* cmdPtr = this->commandsMap[massage];
        cmdPtr->Execute(); // what to insert here?!
    } else {
        // not found
        throw "read Unknown Command from client";
    }


    // remove the thread from threadArr
    refToThreadArr.erase(refToThreadArr.begin()+indexAtThreadArr);
    pthread_exit (NULL); // NULL is to be insert here?!
}

