/*

 */

#ifndef COMMANDPROTOCOL_H_
#define COMMANDPROTOCOL_H_
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class CommandProtocol {
public:
	/**
	 * @param args: paramters for command.
	 * (soket number/name of game/moves)
	 */
	 virtual void Execute(vector<string> args) = 0;
	 virtual ~CommandProtocol() {}
};



#endif /* COMMANDPROTOCOL_H_ */
