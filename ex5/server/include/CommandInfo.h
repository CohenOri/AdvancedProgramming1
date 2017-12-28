//
// Created by ori on 12/27/17.
//

#ifndef ADVANCEDPROGRAMMING1_COMMANDINFO_H
#define ADVANCEDPROGRAMMING1_COMMANDINFO_H

#include <iostream>
#include <string>
#include <map>
using namespace std;

struct CommandInfo {
    int clientSocket;
    string gameName;
    map<string, int>* openGames;

};

#endif //ADVANCEDPROGRAMMING1_COMMANDINFO_H
