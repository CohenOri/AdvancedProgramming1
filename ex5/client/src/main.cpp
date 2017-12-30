/**
# Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */

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
    bool server = false;
    cout << "Let The Game Begin!" << endl;
    cout << "May the odds be ever in your favor\n" << endl;
    do {//ask user against who he wants to play.
        cout << "Choose against who to play\n1-Human local player" << endl;
        cout << "2-AI player" << endl;
        cout << "3-Remote player" << endl;
        cin >> userChoice;
        if (cin.fail() || userChoice > 3 || userChoice < 1) {//check if users input wrong.
            cout << "Illegal input entered or there isn't such option (not in rage 1-3). try again" << endl;
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
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
        	cout << "we arw here" << endl;
     /*       string ip, line;
            int port;
            try {
            ifstream hostInfo("hostInfo.txt");
            if (hostInfo.is_open()) {
                // break the first line into IP
                // break the second line to Port No.
                string delimiter = ":";
                getline(hostInfo, line);
                string token = line.substr(line.find(delimiter) + 1, line.length());
                std::stringstream stream(token);
                stream >> token;
                ip = token;
                getline(hostInfo, line);
                token = line.substr(line.find(delimiter) + 1, line.length());
                std::istringstream(token) >> port; //convert to int
                hostInfo.close();
            } else {
                throw "Unable to open file";
            }
            } catch(const char* msg) {
            	cout << "errorrrrrssss" << msg << endl;
            }
        	cout << "we arw here2" << endl;
**/
            //HostPlayer *p3 = new HostPlayer(ip.c_str(), port);
            HostPlayer *p3 = new HostPlayer("127.0.0.1", 8000);
            try {
                p3->connectToServer();
            //    p3->getSymbolFromServer();
            // p2 = new TerminalPlayer(EnumDeclration::OtherPlayer(p3->getEnumSymbol()));
            } catch (const char *msg) {
                cout << "Failed to connect to server. Reason:" << msg << endl;
                continue;
            		}
            p1 = p3;
            // in order to stop the loop - we've got what we needed (two players)
            correct = true;
            // in order later tell gameFlow that we play with server and not local player
            server = true;

            // Choose command to send the server
            while (true) {
                // print commands menu
                cout << "What would you like to do?\n1-Start new game" << endl;
                cout << "2-Get a list of all open games" << endl;
                cout << "3-Join specific game" << endl;
                int command;
                cin >> command;
                if (cin.fail() || command > 3 || command < 1) {//check if users input wrong.
                    cout << "Illegal input. integers only!" << endl;
                    cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                			}
                    // Start new Game
                else if (command == 1) {
                    cout << "Name your game:\n";
                    string name;
                    cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    //getline(cin, name);
                    cin >> name;
                    // sends start game command to server
                    try {
                       correct = p3->SendStart(name);
                       p3->getSymbolFromServer();
                       p2 = new TerminalPlayer(EnumDeclration::OtherPlayer(p3->getEnumSymbol()));
                       p1 = p3;
                       	   	   	   	   break;
                    } catch (int e) {
                        cout << "Something went wrong, you probably tried to open an already opened game" << endl;
                        continue;
                    				}

                			}
                    // Print open games
                else if (command == 2) {
                    cout << "list of gamed:\n" << endl;
                    // prints the games using the server
                    p3->PrintGamesList();

                    			  correct = false;
                    			  break;
                			}
                    // Join specific game
                else if (command == 3) {
                    cout << "Connect to game:" << endl;
                    cout << "Enter game's name:" << endl;
                    string name;
                    cin.clear();
                   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                   // getline(cin, name);
                    cin >> name;
                    // sends join game command to server
                    try {
                       correct = p3->JoinGame(name);
                       p3->getSymbolFromServer();
                       p1 = p3;
                       p2 = new TerminalPlayer(EnumDeclration::OtherPlayer(p3->getEnumSymbol()));
                    } catch (int e) {
                        cout << "Something went wrong, you probably tried to join non valid game" << endl;
                    continue;
                    			}
                		}
                break;
            }

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
