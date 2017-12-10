
#define BOARD_ROWS 4
#define BOARD_COLS 4

#include <iostream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <string>
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
    // initialize new board, create the objects required for
    // game flow to run and run it.
    Board *b = new Board(BOARD_ROWS, BOARD_COLS);
    RegularLogic rl = RegularLogic(b);
    PlayerInterface *p1 = NULL;
    PlayerInterface *p2 = NULL;
    short userChoice;
    bool correct = false;
    cout << "Let The Game Begin!" << endl;
    cout << "May the odds be ever in your favor\n" << endl;
    do {//ask user against who he wants to play.
        cout << "Choose against who to play\n1-Human local player" << endl;
        cout << "2-AI player" << endl;
        cout << "3-Remote player" << endl;
        cin >> userChoice;
        if (cin.fail()) {//check if users input wrong.
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
            p2 = new AiPlayer(EnumDeclration::O);
        } else if (userChoice == 3) {//play against remote player.
            // Read IP and port of remote Host from file
            string ip, line;
            int port;
            ifstream hostInfo("hostInfo.txt");
            if (hostInfo.is_open()) {
                // break the first line into IP
                // break the second line to Port No.
                string delimiter = ":";
                getline(hostInfo, line);
                string token = line.substr(line.find(delimiter)+1, line.length());
                // remove spaces from the ip/port
                std::remove(token.begin(), token.end(), ' ');
                ip = token;
                getline(hostInfo, line);
                token = line.substr(line.find(delimiter)+1, line.length());
                std::istringstream(token) >> port; //convert to int
                hostInfo.close();
            } else {
                cout << "Unable to open file" << endl;
            }
            //HostPlayer p3("127.0.0.1", 8000); DEFAULT
            cout << "ip read from file: " << ip << endl;
            cout << "port read from file: " << port << endl;
            HostPlayer *p3 = new HostPlayer(ip.c_str(), port);
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
    } while (!correct);
    cin.ignore();
    cout << "you are: 233" << p1->getEnumSymbol() << endl;
    GameFlow gameFlow(&rl, b, p1, p2, false);
    gameFlow.Run();

    //delete members-free memory.
    delete b;
    if (userChoice == 2 || userChoice == 1) {
        delete p2;
    }
    delete p1;
    return 0;
}
