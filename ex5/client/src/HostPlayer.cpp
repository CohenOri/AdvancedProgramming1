/**
# Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755
 */

#include "../include/HostPlayer.h"


HostPlayer::HostPlayer(const char *serverIP, int serverPort) : serverIP(serverIP), serverPort(serverPort),
                                                               clientSocket(0) {
    cout << "Client" << endl;
}

void HostPlayer::connectToServer() {
    // Create a socket point
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
    // htons converts values between host and network byte orders
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;
}

void HostPlayer::getSymbolFromServer() {
    int player;
    int start;
    this->firstMove = true;
    //read which player are you
    int n = read(clientSocket, &player, sizeof(player));
    if (n == -1) {
        throw "Error reading result from socket";
    }//if you 1 mean you are X.
    if (player == 1) {
        this->player = EnumDeclration::X;
        //symbol type here referees to enemy.
        this->symbol = 'O';
        //other player connect when we receive num2 from server.
   /*     cout << "waiting for other player to connect.." << endl;
        int n = read(clientSocket, &start, sizeof(start));
        if (n == -1) {
            throw "Error reading result from socket";
        }**/
        //print to player who is he.
        cout << "you are: X" << endl;
    } else {//if player is 2-he is second.
    	cout << player <<" is what we get" << endl;
        this->player = EnumDeclration::O;
        //symbol type here referees to enemy.
        this->symbol = 'X';
        //print to player who is he.
        cout << "you are: O" << endl;
    }
}

Slot HostPlayer::Play() { return Slot(-1, -1); }

char HostPlayer::GetSymbol() { return this->symbol; }

void HostPlayer::MakeAMove(Board *b, LogicInterface *logic) {
    //first if we End the game-just send Close and return.
    if (b->GetLastMove().compare("Close") == 0) {
        SendMove("Close");
        return;
        //if its the first move-check if the player is X
        //if X return to get from TerminalPlayer a move.
    } else if (firstMove) {
        if (!(this->player == EnumDeclration::O)) {
            this->firstMove = false;
            return;
        }
        //if its not first move-send players move to server.
    } else if (!firstMove) SendMove(b->GetLastMove());
    this->firstMove = false;
    //instalize buffer. read from server array.
    char buffer[50] = {0};
    cout << "Waiting for other player's move..." << endl;
    int n = read(clientSocket, buffer, sizeof(buffer));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    //create a string from the array.
    string answer(buffer);
    //if we got Close-finish the game.
    if (answer.compare("Close") == 0) {
        //update boards last move.
        b->SetLastMove("Close");
        return;
        //if NoMove means other player have no moves
    } else if (answer.compare("NoMove") == 0) {
        b->SetLastMove("NoMove");
        cout << "Enemy has no moves-turn goes back to you." << endl;
        return;//to get new moves

        //we assume that any other move is int, int
    } else {
        ReceiveMove(b, logic, Slot(answer));

    }
}

void HostPlayer::ReceiveMove(Board *b, LogicInterface *logic, Slot move) {
    //place other player move on board and print new board.
    b->SetCellStatus(move.GetRow(), move.GetCol(), EnumDeclration::OtherPlayer((this->player)));
    logic->FlipSlots(move.GetRow(), move.GetCol(), EnumDeclration::OtherPlayer((this->player)));
    //print updated board for player.
    cout << this->symbol << " played: ";
    move.Print();
    cout << endl;
    b->Print();
    //check if its tha last move-if it is-update the board.
    if ((logic->SlotsToPlace(EnumDeclration::X).size() == 0
         && logic->SlotsToPlace(EnumDeclration::O).size() == 0)) {
        b->SetLastMove("Close");
    }
}

void HostPlayer::SendMove(string move) {
    //initialize the buffer array and copy the string.
    char buf[50] = {0};
    size_t length = move.copy(buf, move.size(), 0);
    buf[length] = '\0';
    //send the buffer.
    int n = write(clientSocket, buf, strlen(buf));
    if (n == -1) {
        throw "Error writing move to socket";
    }
}

EnumDeclration::CellStatus HostPlayer::getEnumSymbol() { return EnumDeclration::OtherPlayer((this->player)); }

bool HostPlayer::SendStart(string gameName) {
    // write/send start command to server
    string fullCommand = "start " + gameName;
    WriteCommand(fullCommand);
    int buf;
    //size_t length = fullCommand.copy(buf, fullCommand.size(), 0);
    //buf[length] = '\0';
  //  cout << buf << endl;
    //send the buffer.
    int n = read(clientSocket, &buf, sizeof(buf));
    if (n == -1) {
        throw "Error writing command to socket";
    }
    // validate that server successfully preformed the command
    if(buf == 0) {
    	cout << "wait for other player to conncet" << endl;
    	return true;
    } else if(buf == -1) {
    	cout << "their is such name in the list" << endl;
    	return false;
    }

}

bool HostPlayer::JoinGame(string gameName) {
    // write/send join command to server
    string fullCommand = "join " + gameName;
    WriteCommand(fullCommand);
    int buf;
    //size_t length = fullCommand.copy(buf, fullCommand.size(), 0);
    //buf[length] = '\0';
  //  cout << buf << endl;
    //send the buffer.
    int n = read(clientSocket, &buf, sizeof(buf));
    if (n == -1) {
        throw "Error writing command to socket";
    }
    // validate that server successfully preformed the command
    if(buf == 0) {
    	cout << "0 is answer" << endl;
    	return true;
    } else if(buf == -1) {
    	cout << "-1 is answer" << endl;
    	return false;
    }

}

void HostPlayer::WriteCommand(const string &command) const {
    string fullCommand = command;
    //initialize the buffer array and copy the command.
    char buf[50] = {0};
    size_t length = fullCommand.copy(buf, fullCommand.size(), 0);
    buf[length] = '\0';
    cout << buf << endl;
    //send the buffer.
    int n = write(clientSocket, buf, strlen(buf));
    if (n == -1) {
        throw "Error writing command to socket";
    }
}

void HostPlayer::PrintGamesList() {
    cout << "print Games:" << endl;
    try{
    WriteCommand("list_games");
    } catch (const char *msg) {
    	cout << "error sending: " <<  msg << endl;
    	return;
    }
    bool stop = true;
    while (stop) {
        //initialize buffer. read from server array.
        char massage[50] = {0};
        char* buffer = massage;
        int n = read(clientSocket, buffer, 50);
        if (n == -1) {
            throw "Error reading open games from socket";
        }
        //create a string from the array.
        string answer(massage);
        //if we got end_open_games stop printing.
        if (answer.compare("end_open_games") == 0) {
            // no more open games to print, stop
            stop = false;
        }
        // prints the games
        cout << answer << endl;
    }
}

