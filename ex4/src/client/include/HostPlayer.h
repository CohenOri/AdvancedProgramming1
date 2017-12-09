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
 void connectToServer();
 void getSymbolFromServer();
 virtual Slot Play();
 virtual char GetSymbol();
 virtual void MakeAMove(Board *b, LogicInterface *logic);
 EnumDeclration::CellStatus getEnumSymbol();

 //virtual ~HostPlayer();
private:
 EnumDeclration::CellStatus player;
 char symbol;
 const char *serverIP;
 int serverPort;
 int clientSocket;
 bool firstMove;
 void reciveMove(Board *b, LogicInterface *logic,  Slot move);
 void sendMove(string move);
 bool placeSlotOfPlayer(Board *b,LogicInterface * logic);

};

#endif /* SRC_CLIENT_INCLUDE_HOSTPLAYER_H_ */
