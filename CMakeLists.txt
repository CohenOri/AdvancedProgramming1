cmake_minimum_required(VERSION 3.8)
project(AdvancedProgramming1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        AiPlayer.cpp
        AiPlayer.h
        Board.cpp
        Board.h
        EnumDeclration.h
        GameFlow.cpp
        GameFlow.h
        LogicInterface.h
        main.cpp
        PlayerInterface.h
        RegularLogic.cpp
        RegularLogic.h
        Slot.cpp
        Slot.h
        TerminalPlayer.cpp
        TerminalPlayer.h SlotWithRank.cpp SlotWithRank.h)

add_executable(AdvancedProgramming1 ${SOURCE_FILES})