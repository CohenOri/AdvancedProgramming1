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
    int secces;
    try {
    	secces = 0;
        otherPlayerSocket= this->cmdManager->GetGameSocket(info.gameName);
        cout << "this is other " << otherPlayerSocket << "and this is" << info.clientSocket << endl;
        int n = write(info.clientSocket, &secces, sizeof(secces));
              if (n == -1) {
                  cout << "Error writing to socket" << endl;
                  return;
              } else if (n == 0) {
                  cout << "Client disconnected" << endl;
                  return;
              }
    }
    catch(char const* e) {
    	secces = -1;
        int n = write(info.clientSocket, &secces, sizeof(secces));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        } else if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        cmdManager->deletePlayer(otherPlayerSocket);

        close(info.clientSocket);
        return;
    }

    // Write 1/2 to the player in order to later detrmine which one is the first and second (X/O)
    int playerMode = 1;
    int n = write(otherPlayerSocket, &playerMode, sizeof(playerMode));
    if (n == -1 || n == 0) {
        cout << "Error writing to socket Or Client disconnected" << endl;
        return;}
    playerMode = 2;
    n = write(info.clientSocket, &playerMode, sizeof(playerMode));
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
    int player[] = { otherPlayerSocket, info.clientSocket};
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
        cout << "this is the move " << massage << endl;
        //if the message is Close-return to close connections with players.
        if (strcmp(massage, "Close") == 0) {
            cmdManager->deletePlayer(otherPlayerSocket);
            cmdManager->deletePlayer(info.clientSocket);

            close(player[0]);
            close(player[1]);
            return;
        }
    }
}
