################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Aresta.cpp \
../src/Lista.cpp \
../src/Vertice.cpp \
../src/main.cpp 

OBJS += \
./src/Aresta.o \
./src/Lista.o \
./src/Vertice.o \
./src/main.o 

CPP_DEPS += \
./src/Aresta.d \
./src/Lista.d \
./src/Vertice.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


