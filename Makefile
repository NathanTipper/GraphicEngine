CXX = g++
CXXFLAGS = -Wall -g -std=c++11

CC = gcc
CCFLAGS = -g

SRC_DIR = ./src
INC_DIR = ./include
OBJ_DIR = ./obj
EXE_DIR = ./bin

OBJECTS = $(addprefix $(OBJ_DIR)/, main.o)
LDLIBS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -lXinerama \
-lXcursor -lrt -lm

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	@echo "\n******** Compiling C++ files ********\n"
	$(CXX) -I$(INC_DIR) -c $(CXXFLAGS) $^ -o $@

engine: $(OBJECTS) glad.o | $(EXE_DIR)
	@echo "\n******** Linking ********\n"
	$(CXX) $(CXXFLAGS) -o $(EXE_DIR)/engine $(OBJECTS) $(OBJ_DIR)/glad.o $(LDLIBS) 

glad.o : $(SRC_DIR)/glad.c
	@echo "\n******** Compiling glad ********\n"
	$(CC) -I$(INC_DIR) -c $(CCFLAGS) $^ -o $(OBJ_DIR)/$@

$(OBJECTS) : | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(EXE_DIR):
	mkdir $(EXE_DIR)

.PHONY : clean cleanall
clean:
	rm -fr obj bin *~

cleanall: clean
	rm -fr src/*~ include/*~
