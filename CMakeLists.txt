cmake_minimum_required(VERSION 3.8)
project(AdvancedProgramming1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ex5/src/client/include/AiPlayer.h
        ex5/src/client/include/Board.h
        ex5/src/client/include/EnumDeclration.h
        ex5/src/client/include/GameFlow.h
        ex5/src/client/include/HostPlayer.h
        ex5/src/client/include/LogicInterface.h
        ex5/src/client/include/PlayerInterface.h
        ex5/src/client/include/RegularLogic.h
        ex5/src/client/include/Slot.h
        ex5/src/client/include/SlotWithRank.h
        ex5/src/client/include/TerminalPlayer.h
        ex5/src/client/src/AiPlayer.cpp
        ex5/src/client/src/Board.cpp
        ex5/src/client/src/GameFlow.cpp
        ex5/src/client/src/HostPlayer.cpp
        ex5/src/client/src/main.cpp
        ex5/src/client/src/RegularLogic.cpp
        ex5/src/client/src/Slot.cpp
        ex5/src/client/src/SlotWithRank.cpp
        ex5/src/client/src/TerminalPlayer.cpp
        ex5/src/server/include/CommandInfo.h
        ex5/src/server/include/CommandManager.h
        ex5/src/server/include/CommandProtocol.h
        ex5/src/server/include/GameControl.h
        ex5/src/server/include/JoinToGame.h
        ex5/src/server/include/PrintGames.h
        ex5/src/server/include/Server.h
        ex5/src/server/include/StartNewGame.h
        ex5/src/server/src/CommandManager.cpp
        ex5/src/server/src/GameControl.cpp
        ex5/src/server/src/JoinToGame.cpp
        ex5/src/server/src/main.cpp
        ex5/src/server/src/PrintGames.cpp
        ex5/src/server/src/Server.cpp
        ex5/src/server/src/StartNewGame.cpp)

add_executable(AdvancedProgramming1 ${SOURCE_FILES})