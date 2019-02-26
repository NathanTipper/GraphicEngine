CXX = g++
CXXFLAGS = -Wall -g

CC = gcc
CCFLAGS = -g

OBJECTS = $(addprefix $(OBJ_DIR)/, main.o)
LDLIBS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -lXinerama \
-lXcursor -lrt -lm

SRC_DIR = ./src
INC_DIR = ./include
OBJ_DIR = ./obj

$(OBJ_DIR)/%.o : %.cc
	$(CXX) -I$(INC_DIR) -c $(CXXFLAGS) $^ -o $@

engine: $(OBJECTS) glad.o
	@echo Starting installation
	$(CXX) $(CXXFLAGS) -o engine $(OBJECTS) $(LDLIBS) 

glad.o : glad/glad.h
	$(CC) -I$(INC_DIR) -c $(CCFLAGS) $^ -o $(OBJ_DIR)/$@

$(OBJECTS) : | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir obj

.PHONY : clean cleanall
clean:
	rm -fr obj *~ engine

cleanall: clean
	rm -fr src/*~ include/*~
