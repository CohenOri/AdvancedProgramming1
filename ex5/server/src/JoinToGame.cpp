/*
 * JoinToGame.cpp
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#include "../include/JoinToGame.h"

JoinToGame::JoinToGame(CommandManager *cmdManagerPtr) {
    this->cmdManager = cmdManagerPtr;
}

JoinToGame::~JoinToGame() {
}


void JoinToGame::Execute(struct CommandInfo info) {
    int otherPlayerSocket;
    try {
        otherPlayerSocket= this->cmdManager->GetGameSocket(info.gameName);}
    catch(int e) {
        int n = write(info.clientSocket, "-1", sizeof("-1"));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        } else if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        close(info.clientSocket);
        return;
    }

    // Write 1/2 to the player in order to later detrmine which one is the first and second (X/O)
    int n = write(otherPlayerSocket, "1", sizeof("1"));
    if (n == -1 || n == 0) {
        cout << "Error writing to socket Or Client disconnected" << endl;
        return;}
    n = write(info.clientSocket, "2", sizeof("2"));
    if (n == -1 || n == 0) {
        cout << "Error writing to socket Or Client disconnected" << endl;
        return;}

    // Remove the game from the NameToGameMap
    if(this->cmdManager->RemoveGame(info.gameName)){
        // successfully removed the game - so there is no way 3 clients will try to connect to the same game
        // because the 3rd one was an idiot
    } else {
        throw "Couldn't Remove the game because couldn't find such game";
    }

    // Read the plays from each client until game is over
    int player[] = {info.clientSocket, otherPlayerSocket};
    int turnCounter = 0;
    char buffer[50];
    char *massage = buffer;
    while (true) {
        memset(buffer, 0, 50);//empty the values.
        // Read massage from player.
        n = read(player[turnCounter % 2], massage, sizeof(massage));
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
        //if the message is Close-return to close connections with players.
        if (strcmp(massage, "Close") == 0) {
            close(player[0]);
            close(player[1]);
        }
    }
}