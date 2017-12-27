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
    int otherPlayerSocket = this->cmdManager->GetGameSocket(info.gameName);

    // im not sure how to send the "start" message?!
    int player[] = {info.clientSocket, otherPlayerSocket};
    int turnCounter = 0;
    char buffer[50];
    char *massage = buffer;
    while (true) {
        memset(buffer, 0, 50);//empty the values.
        // Read massage from player.
        int n = read(player[turnCounter % 2], massage, sizeof(massage));
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
            /**
             * Preform close of the game
             */
            if(this->cmdManager->RemoveGame(info.gameName)){
                return;
            }
            throw "Couldn't close the game because couldn't find such game";
        }
    }
}