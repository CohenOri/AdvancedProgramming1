/*
 * PrintGames.cpp
 *
 *  Created on: 27 בדצמ׳ 2017
 *      Author: yanap
 */

#include "../include/PrintGames.h"

PrintGames::PrintGames(CommandManager *cmdManagerPtr) {
    this->cmdManager = cmdManagerPtr;
}

PrintGames::~PrintGames() {
}

vector<string> PrintGames::Execute(struct CommandInfo info) {
    return this->cmdManager->ListOfGamesNames();
}

