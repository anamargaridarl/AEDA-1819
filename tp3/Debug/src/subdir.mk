################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Test.cpp \
../src/animal.cpp \
../src/veterinario.cpp \
../src/zoo.cpp 

OBJS += \
./src/Test.o \
./src/animal.o \
./src/veterinario.o \
./src/zoo.o 

CPP_DEPS += \
./src/Test.d \
./src/animal.d \
./src/veterinario.d \
./src/zoo.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1z -I"/home/anamargaridarl/Documents/AEDA/tp3 final/cute" -I"/home/anamargaridarl/Documents/AEDA/tp3 final/boost" -O0 -g3 -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


