CXX = g++
CXXFLAGS = -Wall -g

SRC = ./obj/
INC = ./include/

engine: main.o
	$(CXX) $(CXXFLAGS) -o engine main.o
