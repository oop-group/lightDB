CROSS =   
CXX = $(CROSS)g++  
CFLAGS = -Wall -c -std=c++11

RM = -rm

SRCS = $(wildcard ./controller/*.cpp ./core/*.cpp ./os/*.cpp ./parser/*.cpp ./rename/*.cpp *.cpp)  

OBJS = $(patsubst %.cpp, %.o, $(SRCS))  

VERSION = 1.0.0.0  
TARGET = main 
  
all:$(TARGET)  
	
$(TARGET) : $(OBJS)  
	$(CXX) $^ -o $@  
  
$(OBJS):%.o : %.cpp  
	$(CXX) $(CFLAGS) $< -o $@  
.PHONY : clean
clean :  
	$(RM) $(TARGET) $(OBJS)  
