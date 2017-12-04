################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/client/gtest_src/gtest-all.cc 

CC_DEPS += \
./src/client/gtest_src/gtest-all.d 

OBJS += \
./src/client/gtest_src/gtest-all.o 


# Each subdirectory must supply rules for building sources it contributes
src/client/gtest_src/%.o: ../src/client/gtest_src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/gtest -I"/home/yanap/שולחן העבודה/BarIlan/ex4" -I/home/yanap/googletest/googletest/include -I/usr/src/gtest -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


