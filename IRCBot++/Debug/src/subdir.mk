################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Configuration.cpp \
../src/Controller.cpp \
../src/Database.cpp \
../src/IRCBot++.cpp \
../src/Log.cpp \
../src/Server.cpp \
../src/function.cpp 

OBJS += \
./src/Configuration.o \
./src/Controller.o \
./src/Database.o \
./src/IRCBot++.o \
./src/Log.o \
./src/Server.o \
./src/function.o 

CPP_DEPS += \
./src/Configuration.d \
./src/Controller.d \
./src/Database.d \
./src/IRCBot++.d \
./src/Log.d \
./src/Server.d \
./src/function.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/develop/Arbeitsfläche/IRCBot/libircclient/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


