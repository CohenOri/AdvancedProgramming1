


#include "../include/GameControl.h"

GameControl::GameControl(CommandManager* game) {
	//this->server = server;
	this->gameList = game;
	this->commandsMap["start"] = new StartNewGame(gameList);
	this->commandsMap["list_games"] = new PrintGames(gameList);
	this->commandsMap["join"] = new JoinToGame(gameList);
}

GameControl::~GameControl() {
	map<string, CommandProtocol *>::iterator it;
	 for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
		 	 delete it->second;
	 }
}


bool GameControl::executeCommand(string command, CommandInfo args) {
	if (this->commandsMap.find(command) != this->commandsMap.end() )  {
		CommandProtocol* cmdPtr = this->commandsMap[command];
		this->gameList->addPlayer(args.clientSocket);
		cmdPtr->Execute(args);
		return true;
	}
	return false;
}

void GameControl::End() {
	this->gameList->closeAllPlayers();
}



