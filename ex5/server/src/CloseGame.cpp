/*
 * CloseGame.cpp
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#include "../include/CloseGame.h"


CloseGame::CloseGame(CommandManager *cmdManagerPtr) {
    this->cmdManager = cmdManagerPtr;
}

CloseGame::~CloseGame() {
}

void CloseGame::Execute(struct CommandInfo info) {
    if(this->cmdManager->RemoveGame(info.gameName)){
        return;
    }
    throw "Couldn't close the game because couldn't find such game";
}

