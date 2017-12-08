cmake_minimum_required(VERSION 3.8)
project(AdvancedProgramming1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    ex4/src/client/include/AiPlayer.h
    ex4/src/client/include/Board.h
    ex4/src/client/include/EnumDeclration.h
    ex4/src/client/include/GameFlow.h
    ex4/src/client/include/HostPlayer.h
    ex4/src/client/include/LogicInterface.h
    ex4/src/client/include/PlayerInterface.h
    ex4/src/client/include/RegularLogic.h
    ex4/src/client/include/Slot.h
    ex4/src/client/include/SlotWithRank.h
    ex4/src/client/include/TerminalPlayer.h
    ex4/src/client/src/AiPlayer.cpp
    ex4/src/client/src/Board.cpp
    ex4/src/client/src/GameFlow.cpp
    ex4/src/client/src/HostPlayer.cpp
    ex4/src/client/src/main.cpp
    ex4/src/client/src/RegularLogic.cpp
    ex4/src/client/src/Slot.cpp
    ex4/src/client/src/SlotWithRank.cpp
    ex4/src/client/src/TerminalPlayer.cpp
    #[[ex4/src/server/main.cpp]]
    ex4/src/server/Server.cpp
    ex4/src/server/Server.h)

add_executable(AdvancedProgramming1 ${SOURCE_FILES})