/*

 */

#ifndef COMMANDPROTOCOL_H_
#define COMMANDPROTOCOL_H_
#include <vector>
#include <string>
#include <iostream>

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
