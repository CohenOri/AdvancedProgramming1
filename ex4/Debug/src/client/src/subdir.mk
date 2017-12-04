################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/client/src/AiPlayer.cpp \
../src/client/src/Board.cpp \
../src/client/src/GameFlow.cpp \
../src/client/src/HostPlayer.cpp \
../src/client/src/RegularLogic.cpp \
../src/client/src/Slot.cpp \
../src/client/src/SlotWithRank.cpp \
../src/client/src/TerminalPlayer.cpp \
../src/client/src/main.cpp 

OBJS += \
./src/client/src/AiPlayer.o \
./src/client/src/Board.o \
./src/client/src/GameFlow.o \
./src/client/src/HostPlayer.o \
./src/client/src/RegularLogic.o \
./src/client/src/Slot.o \
./src/client/src/SlotWithRank.o \
./src/client/src/TerminalPlayer.o \
./src/client/src/main.o 

CPP_DEPS += \
./src/client/src/AiPlayer.d \
./src/client/src/Board.d \
./src/client/src/GameFlow.d \
./src/client/src/HostPlayer.d \
./src/client/src/RegularLogic.d \
./src/client/src/Slot.d \
./src/client/src/SlotWithRank.d \
./src/client/src/TerminalPlayer.d \
./src/client/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/client/src/%.o: ../src/client/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


