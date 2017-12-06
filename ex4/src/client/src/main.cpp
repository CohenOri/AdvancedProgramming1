

#include <iostream>
#include <limits>
#include "../include/Board.h"
#include <sstream>

#include "../include/RegularLogic.h"
#include "../include/GameFlow.h"
#include "../include/TerminalPlayer.h"
#include "../include/AiPlayer.h"
#include "../include/PlayerInterface.h"
#include "../include/HostPlayer.h"

using namespace std;

int main() {
  // initialize new board_, create the objects requried for
  // game flow to run and run it.
  Board* b = new Board(4, 4);
  RegularLogic rl = RegularLogic(b);
  PlayerInterface * p1 = NULL;
  PlayerInterface* p2 = NULL;
  short userChoice;
  bool correct = false;
	cout << "Let The Game Begin!" << endl;
	cout << "May the odds be ever in your favor\n" << endl;
  do {//ask user against who he wants to play.
		cout << "Choose against who to play\n1-Humen local player" << endl;
		cout << "2-AI player" << endl;
		cout << "3-Remote player" << endl;
		cin >> userChoice;
		if(cin.fail()) {//check if users input wrong.
			cout << "Illegal input. integers only!" << endl;
			cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} else if (userChoice == 1) {//play against human.
			correct = true;
			p1 = new TerminalPlayer(EnumDeclration::X);
			p2 = new TerminalPlayer(EnumDeclration::O);
		} else if (userChoice == 2) {//play against computer.
			correct = true;
			p1 = new TerminalPlayer(EnumDeclration::X);
			p2 =new  AiPlayer(EnumDeclration::O);
		} else if (userChoice == 3) {
			//HostPlayer p3("127.0.0.1", 8000);
			HostPlayer *p3 = new HostPlayer("127.0.0.1", 8000);
			try {
				p3->connectToServer();
				p3->getSymbolFromServer();
			} catch (const char *msg) {
				 cout << "Failed to connect to server. Reason:" << msg << endl;
			}
			p1 = p3;
			correct = true;
		} else {//if input is taken or against the
			cout << "no such option. choose again" << endl;
		}
	} while(!correct);
  cin.ignore();
	cout << "you are: 233" << p1->getEnumSymbol() << endl;
  GameFlow gameFlow(&rl, b, p1, p2);
  gameFlow.Run();

  //delete members-free memory.
  delete b;
  if (userChoice == 2 || userChoice == 1) {
	  delete p2;
  }
  delete p1;
  return 0;
}
