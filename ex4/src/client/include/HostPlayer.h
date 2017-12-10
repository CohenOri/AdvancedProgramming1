/*
 * HostPlayer.h
 *
 *  Created on: 2 בדצמ׳ 2017
 *      Author: yanap
 */

#ifndef SRC_CLIENT_INCLUDE_HOSTPLAYER_H_
#define SRC_CLIENT_INCLUDE_HOSTPLAYER_H_
#include "PlayerInterface.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
using namespace std;
class HostPlayer: public PlayerInterface {
public:
	HostPlayer(const char *serverIP, int serverPort);
	/**
	 * conntect to the sever by the ip and port.
	 */
 void connectToServer();
 /**
  * read from the server for the first time.
  * if the number is 1 the player is X and wait to other player.
  * else player is O.
  */
 void getSymbolFromServer();
 /**
  * do nothing.
  * @return -1 -1 for error check.
  */
 virtual Slot Play();
 virtual char GetSymbol();
 virtual void MakeAMove(Board *b, LogicInterface *logic);
 EnumDeclration::CellStatus getEnumSymbol();

private:
 EnumDeclration::CellStatus player;
 char symbol;
 const char *serverIP;
 int serverPort;
 int clientSocket;
 bool firstMove;
 /**
  * place enemy's move on the board and flip the slots.
  * @param b pointer for board.
  * @param logic - for the game rulls.
  * @param slot to place.
  */
 void ReciveMove(Board *b, LogicInterface *logic,  Slot move);
 /**
  * send to the server last move on the board.
  */
 void SendMove(string move);

};

#endif /* SRC_CLIENT_INCLUDE_HOSTPLAYER_H_ */
