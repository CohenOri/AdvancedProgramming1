//
// Created by ori on 12/27/17.
//

#ifndef ADVANCEDPROGRAMMING1_COMMANDMANAGER_H
#define ADVANCEDPROGRAMMING1_COMMANDMANAGER_H
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

//#include "CommandProtocol.h"
#include <map>
/**
#include "PlayMove.h"
#include "StartNewGame.h"
#include "JoinToGame.h"
#include "CloseGame.h"
#include "PrintGames.h"
**/

class CommandManager {
public:
    CommandManager();
   // CommandProtocol* GetCommand(string cmdName);
    /**
     *
     * @param gameName
     * @param gameSocket
     * @return true if added new game, false if didn't add new game (there's already
     * game with this name)
     */
    bool AddGame(string gameName, int gameSocket);
    int GetGameSocket(string gameName);
    vector<string> ListOfGamesNames();
    void addPlayer(int player);
    void deletePlayer(int pkayer);
    void closeAllPlayers();
    /**
     * @param gameName
     * @return true if successfully closed the game, false otherwise
     */
    bool RemoveGame(string gameName);

private:
    vector<int> connectedPlayers;
    map<string, int> nameToGameMap;
    pthread_mutex_t mutex;

};


#endif //ADVANCEDPROGRAMMING1_COMMANDMANAGER_H
