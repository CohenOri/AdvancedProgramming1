
#define BOARD_ROWS 4
#define BOARD_COLS 4

#include <iostream>
#include <limits>
#include <fstream>
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
    bool server = false;
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
            /**
             * Read IP and port of remote Host from file
             */

            /**FILE *hostInfo = fopen("hostInfo.txt", "rb");
            char buffer[BUFFSIZE];
            size_t bytes;
            if (hostInfo == NULL) {
                // Failed opening file...
                return 0;
            }
            // as long as there bytes to copy copy them
            while ((bytes = fread(buffer, 1, BUFFSIZE, hostInfo)) != 0) {
            }
            fclose(hostInfo);
string ipNumber;
            str
            string line;
            ifstream hostInfo("hostInfo.txt");
            if (hostInfo.is_open())
            {
                while ( getline (hostInfo,line) )
                {
                    //REMOVE THIS LINE cout << line << '\n';
                    // break the first line into IP
                    // break the second line to Port No.
                    string delimiter = ": ";
                    string token = line.substr(1, line.find(delimiter));
                }
                hostInfo.close();
            }
            else cout << "Unable to open file";

*/
            //HostPlayer p3("127.0.0.1", 8000);
            HostPlayer *p3 = new HostPlayer("127.0.0.1", 8000);
            try {
                p3->connectToServer();
                p3->getSymbolFromServer();
                p2 = new TerminalPlayer(EnumDeclration::OtherPlayer(p3->getEnumSymbol()));
               // p2 = new TerminalPlayer(p3->getEnumSymbol());
            } catch (const char *msg) {
                cout << "Failed to connect to server. Reason:" << msg << endl;
            }
            p1 = p3;
            correct = true;
            server = true;
        } else {//if input is taken or against the
            cout << "no such option. choose again" << endl;
        }
    } while (!correct);
    cin.ignore();
    GameFlow gameFlow(&rl, b, p1, p2, server);
    gameFlow.Run();

    //delete members-free memory.
    delete b;
    delete p2;
    delete p1;
    return 0;
}
