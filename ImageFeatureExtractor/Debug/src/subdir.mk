#Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FeatureExtractor.cpp \
../src/FeatureVec.cpp 

OBJS += \
./src/FeatureExtractor.o \
./src/FeatureVec.o 

CPP_DEPS += \
./src/FeatureExtractor.d \
./src/FeatureVec.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/share/apps/opencv/2.4.10/intel/include/opencv -I/share/apps/opencv/2.4.10/intel/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



