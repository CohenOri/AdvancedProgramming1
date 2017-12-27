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

int StartNewGame::Execute(struct CommandInfo info) {
    if(this->cmdManager->AddGame(info.gameName, info.clientSocket)){
     return 0;
    }
    return -1;
}

