cmake_minimum_required(VERSION 3.8)
project(AdvancedProgramming1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        gtest_src/gtest-all.cc
        gtest_src/gtest.h
        include/AiPlayer.h
        include/Board.h
        include/EnumDeclration.h
        include/GameFlow.h
        include/LogicInterface.h
        include/PlayerInterface.h
        include/RegularLogic.h
        include/Slot.h
        include/SlotWithRank.h
        include/TerminalPlayer.h
        src/AiPlayer.cpp
        src/Board.cpp
        src/GameFlow.cpp
        src/main.cpp
        src/RegularLogic.cpp
        src/Slot.cpp
        src/SlotWithRank.cpp
        src/TerminalPlayer.cpp
        test/AdvanceTestGame.h
        test/test-all.cpp
        test/TestAiPlayer.h
        test/TestClassicLogic.h
        test/TestManager.cpp)

add_executable(AdvancedProgramming1 ${SOURCE_FILES})