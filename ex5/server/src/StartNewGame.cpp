/*
 * StartNewGame.cpp
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#include "../include/StartNewGame.h"

StartNewGame::StartNewGame(CommandManager* cmdManagerPtr) {
    this->cmdManager = cmdManagerPtr;
}

StartNewGame::~StartNewGame() {
}

void StartNewGame::Execute(struct CommandInfo info) {
    // if successfully added the game
    if(this->cmdManager->AddGame(info.gameName, info.clientSocket)){
        int n = write(info.clientSocket, "0", strlen("0"));
        if (n == -1) {
            throw "Error writing to socket";
        }
        return;
    }
    int n = write(info.clientSocket, "-1", strlen("-1"));
    close(info.clientSocket);
    if (n == -1) {
        throw "Error writing to socket";
    }
}

