//
// Created by ori on 12/27/17.
//

#include "CommandManager.h"


CommandManager::CommandManager() {
    pthread_mutex_lock(&this->mutex);
    this->commandsMap["start"] = StartNewGame(this);
    this->commandsMap["list_games"] = PrintGames(this);
    this->commandsMap["join"] = JoinToGame(this);
    this->commandsMap["play"] = PlayMove(this);
    this->commandsMap["close"] = CloseGame(this);
    pthread_mutex_unlock(&this->mutex);
}

CommandProtocol CommandManager::GetCommand(string cmdName) {
    pthread_mutex_lock(&this->mutex);
    if (this->commandsMap.find(cmdName) != this->commandsMap.end()) {
        // found the command - return her
        pthread_mutex_unlock(&this->mutex);
        return this->commandsMap[cmdName];
    } else {
        // couldn't find the command
        throw "GetCommand failed, there is no such Command";
    }
}

bool CommandManager::AddGame(string gameName, int gameSocket) {
    pthread_mutex_lock(&this->mutex);
    if (this->nameToGameMap.find(gameName) != this->nameToGameMap.end()) {
        // found game with given name, don't add anything and return you didn't
        pthread_mutex_unlock(&this->mutex);
        return false;
    }
    // otherwise, add the game to NameToGame map, return you did
    this->nameToGameMap[gameName] = gameSocket;
    pthread_mutex_unlock(&this->mutex);
    return true;
}

int CommandManager::GetGameSocket(string gameName) const {
    pthread_mutex_lock(&this->mutex);
    if (this->nameToGameMap.find(gameName) != this->nameToGameMap.end()) {
        // found the gameSocket - return it
        pthread_mutex_unlock(&this->mutex);
        return this->nameToGameMap[gameName];
    } else {
        // couldn't find the gameSocket
        throw "GetGameSocket failed, there is no such GameSocket, Are you sure you've added it first?";
    }
}

vector<string> CommandManager::ListOfGamesNames() const {
    pthread_mutex_lock(&this->mutex);
    vector<string> listOfGamesNames;
    map<string, int>::const_iterator it;
    for (it = this->nameToGameMap.begin(); it != this->nameToGameMap.end(); it++) {
        listOfGamesNames.push_back(it->first);
    }
    pthread_mutex_unlock(&this->mutex);
    return listOfGamesNames;
}

bool CommandManager::RemoveGame(string gameName) {
    pthread_mutex_lock(&this->mutex);
    if (this->nameToGameMap.find(gameName) != this->nameToGameMap.end()) {
        // found the gameSocket - close it and return true
        this->nameToGameMap.erase(gameName); // close the game
        pthread_mutex_unlock(&this->mutex);
        return true;
    }
    // couldn't find the game to close
    pthread_mutex_unlock(&this->mutex);
    return false;
}



