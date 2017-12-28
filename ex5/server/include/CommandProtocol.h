/*

 */

#ifndef COMMANDPROTOCOL_H_
#define COMMANDPROTOCOL_H_
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "CommandInfo.h"

using namespace std;

/**
 * Interface for commands
 */
class CommandProtocol {
public:
	/**
	 * @param args: paramters for command.
	 * (soket number/name of game/moves)
	 */
	 virtual void Execute(struct CommandInfo info) = 0;
	 virtual ~CommandProtocol() {}
};



#endif /* COMMANDPROTOCOL_H_ */
