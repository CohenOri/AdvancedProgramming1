################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AiPlayer.cpp \
../src/Board.cpp \
../src/GameFlow.cpp \
../src/RegularLogic.cpp \
../src/Slot.cpp \
../src/SlotWithRank.cpp \
../src/TerminalPlayer.cpp \
../src/main.cpp 

OBJS += \
./src/AiPlayer.o \
./src/Board.o \
./src/GameFlow.o \
./src/RegularLogic.o \
./src/Slot.o \
./src/SlotWithRank.o \
./src/TerminalPlayer.o \
./src/main.o 

CPP_DEPS += \
./src/AiPlayer.d \
./src/Board.d \
./src/GameFlow.d \
./src/RegularLogic.d \
./src/Slot.d \
./src/SlotWithRank.d \
./src/TerminalPlayer.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


