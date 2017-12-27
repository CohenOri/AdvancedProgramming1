cmake_minimum_required(VERSION 3.8)
project(AdvancedProgramming1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ex5/client/gtest_src/gtest-all.cc
        ex5/client/gtest_src/gtest.h
        ex5/client/include/AiPlayer.h
        ex5/client/include/Board.h
        ex5/client/include/EnumDeclration.h
        ex5/client/include/GameFlow.h
        ex5/client/include/HostPlayer.h
        ex5/client/include/LogicInterface.h
        ex5/client/include/PlayerInterface.h
        ex5/client/include/RegularLogic.h
        ex5/client/include/Slot.h
        ex5/client/include/SlotWithRank.h
        ex5/client/include/TerminalPlayer.h
        ex5/client/src/AiPlayer.cpp
        ex5/client/src/Board.cpp
        ex5/client/src/GameFlow.cpp
        ex5/client/src/HostPlayer.cpp
        ex5/client/src/main.cpp
        ex5/client/src/RegularLogic.cpp
        ex5/client/src/Slot.cpp
        ex5/client/src/SlotWithRank.cpp
        ex5/client/src/TerminalPlayer.cpp
        ex5/client/test/AdvanceTestGame.h
        ex5/client/test/test-all.cpp
        ex5/client/test/TestAiPlayer.h
        ex5/client/test/TestClassicLogic.h
        ex5/client/test/TestManager.cpp
        ex5/server/include/CloseGame.h
        ex5/server/include/CommandProtocol.h
        ex5/server/src/GameControl.cpp
        ex5/server/include/GameControl.h
        ex5/server/include/JoinToGame.h
        ex5/server/include/PlayMove.h
        ex5/server/include/PrintGames.h
        ex5/server/include/Server.h
        ex5/server/include/StartNewGame.h
        ex5/server/src/CloseGame.cpp
        ex5/server/src/JoinToGame.cpp
        ex5/server/src/main.cpp
        ex5/server/src/PlayMove.cpp
        ex5/server/src/PrintGames.cpp
        ex5/server/src/Server.cpp
        ex5/server/src/StartNewGame.cpp
        ex5/info.txt ex5/server/src/CheckNewClient.cpp ex5/server/include/CheckNewClient.h)

add_executable(AdvancedProgramming1 ${SOURCE_FILES})