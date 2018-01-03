/*
 * PrintGames.cpp
 *
 *  Created on: 27 בדצמ׳ 2017
 *      Author: yanap
 */

#include "../include/PrintGames.h"

PrintGames::PrintGames(GameControl *gameControl) {
    this->gameControl = gameControl;
}

PrintGames::~PrintGames() {
}

void PrintGames::Execute(struct CommandInfo info) {
    vector<string> gamesNames = this->gameControl->ListOfGamesNames();
    vector<string>::const_iterator it;
    if (gamesNames.size() == 0) {
        char buf[50] = {0};
        char *noGameString = buf;
        string end = "No Open Game";
        size_t length = end.copy(buf, end.size(), 0);
        buf[length] = '\0';
        //send the buffer.
        int n = write(info.clientSocket, noGameString, sizeof(noGameString));
        if (n == -1) {
            throw "Error writing to socket";
        }
    } else {
        // prints each game
        for (it = gamesNames.begin(); it != gamesNames.end(); it++) {
            //initialize the buffer array and copy the string.
            //////////cout << *it << endl;
            char buf[50] = {0};
            size_t length = (*it).copy(buf, (*it).size(), 0);
            buf[length] = '\0';
            //send the buffer.
            int n = write(info.clientSocket, &buf, sizeof(buf));
            if (n == -1) {
                throw "Error writing to socket";
            }
        }
    }
    char buf[50] = {0};
    char *endOpenGamesStr = buf;
    string end = "end_open_games";
    size_t length = end.copy(buf, end.size(), 0);
    buf[length] = '\0';
    //send the buffer.
    int n = write(info.clientSocket, endOpenGamesStr, sizeof(buf));
    if (n == -1) {
        throw "Error writing to socket";
    }
    close(info.clientSocket);
    gameControl->DeletePlayer(info.clientSocket);
}

