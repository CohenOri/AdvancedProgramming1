//
// Created by ori on 12/27/17.
//

#ifndef ADVANCEDPROGRAMMING1_COMMANDMANAGER_H
#define ADVANCEDPROGRAMMING1_COMMANDMANAGER_H

#include "CommandProtocol.h"
#include <map>

#include "PlayMove.h"
#include "StartNewGame.h"
#include "JoinToGame.h"
#include "CloseGame.h"
#include "PrintGames.h"

#include <pthread.h>

class CommandManager {
public:
    CommandManager();
    CommandProtocol GetCommand(string cmdName);
    /**
     *
     * @param gameName
     * @param gameSocket
     * @return true if added new game, false if didn't add new game (there's already
     * game with this name)
     */
    bool AddGame(string gameName, int gameSocket);
    int GetGameSocket(string gameName) const;
    vector<string> ListOfGamesNames() const;
    /**
     * @param gameName
     * @return true if successfully closed the game, false otherwise
     */
    bool RemoveGame(string gameName);

private:
    map<string, CommandProtocol> commandsMap;
    map<string, int> nameToGameMap;
    pthread_mutex_t mutex;

};


#endif //ADVANCEDPROGRAMMING1_COMMANDMANAGER_H
