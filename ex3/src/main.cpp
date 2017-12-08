

#include <iostream>
#include <limits>
#include "../include/Board.h"

#include "../include/RegularLogic.h"
#include "../include/GameFlow.h"
#include "../include/TerminalPlayer.h"
#include "../include/AiPlayer.h"
#include "../include/PlayerInterface.h"

using namespace std;

int main() {
  // initialize new board_, create the objects requried for
  // game flow to run and run it.
  Board* b = new Board();
  RegularLogic rl = RegularLogic(b);
  TerminalPlayer p1 = TerminalPlayer(EnumDeclration::X);
  PlayerInterface* p2;
  short userChoice;
  bool correct = false;
	cout << "Let The Game Begin!" << endl;
	cout << "May the odds be ever in your favor\n" << endl;
  do {//ask user against who he wants to play.
		cout << "Choose against who to play\n1-Humen player(you friend)." << endl;
		cout << "2-Computer" << endl;
		cin >> userChoice;
		if(cin.fail()) {//check if users input wrong.
			cout << "Illegal input. integers only!" << endl;
			cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} else if (userChoice == 1) {//play against human.
			correct = true;
			 p2 = new TerminalPlayer(EnumDeclration::O);
		} else if (userChoice == 2) {//play against computer.
			correct = true;
			 p2 =new  AiPlayer(EnumDeclration::O);
		} else {//if input is taken or against the
			cout << "no such option. choose again" << endl;
		}
	} while(!correct);
  cin.ignore();
  GameFlow gameFlow(&rl, b, &p1, p2);
  gameFlow.Run();

  //delete members-free memory.
  delete b;
  delete p2;
  return 0;
}