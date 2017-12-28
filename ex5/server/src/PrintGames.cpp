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

void PrintGames::Execute(struct CommandInfo info) {
    vector<string> gamesNames = this->cmdManager->ListOfGamesNames();
    vector<string>::const_iterator it;
    for (it = gamesNames.begin(); it != gamesNames.end(); it++) {
        // *it = the gameName[i]
        //initialize the buffer array and copy the string.
        char buf[50] = {0};
        size_t length = (*it).copy(buf,(*it).size(),0);
        buf[length]='\0';
        //send the buffer.
        int n = write(info.clientSocket, buf, strlen(buf));
        if (n == -1) {
            throw "Error writing to socket";
        }
    }
    char buf[50] = {0};
    string end = "end_open_games";
      size_t length = (end).copy(buf,(end).size(),0);
      buf[length]='\0';
      //send the buffer.
      int n = write(info.clientSocket, buf, strlen(buf));
      if (n == -1) {
          throw "Error writing to socket";
      }
    cmdManager->deletePlayer(info.clientSocket);
    close(info.clientSocket);
}

