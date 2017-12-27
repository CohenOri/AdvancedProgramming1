/*
 * PlayMove.cpp
 *
 *  Created on: 24 בדצמ׳ 2017
 *      Author: yanap
 */

#include "../include/PlayMove.h"


PlayMove::PlayMove(CommandManager *cmdManagerPtr) {
    this->cmdManager = cmdManagerPtr;
}

PlayMove::~PlayMove() {

}

void PlayMove::Execute(struct CommandInfo info) {
    int otherPlayerSocket = this->cmdManager->GetGameSocket(info.gameName);

    // idk how to send the Play?!
}


