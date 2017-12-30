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
	int tru;
    if(this->cmdManager->AddGame(info.gameName, info.clientSocket)){
    	tru = 0;
        int n = write(info.clientSocket, &tru, sizeof(tru));
        if (n == -1) {
            throw "Error writing to socket";
        }
        return;
    }
    tru = -1;
    int n = write(info.clientSocket, &tru, sizeof(tru));
    cmdManager->deletePlayer(info.clientSocket);
    close(info.clientSocket);
    if (n == -1) {
        throw "Error writing to socket";
    }
}

