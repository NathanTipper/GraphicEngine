CXX = g++
CXXFLAGS = -Wall -g

CC = gcc
CCFLAGS = -g

SRC_DIR = ./src
INC_DIR = ./include
OBJ_DIR = ./obj

OBJECTS = $(addprefix $(OBJ_DIR)/, main.o)
LDLIBS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -lXinerama \
-lXcursor -lrt -lm

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	@echo compiling c++ files
	$(CXX) -I$(INC_DIR) -c $(CXXFLAGS) $^ -o $@

engine: $(OBJECTS) glad.o
	@echo Starting installation
	$(CXX) $(CXXFLAGS) -o engine $(OBJECTS) $(OBJ_DIR)/glad.o $(LDLIBS) 

glad.o : $(SRC_DIR)/glad.c
	@echo Compiling glad
	$(CC) -I$(INC_DIR) -c $(CCFLAGS) $^ -o $(OBJ_DIR)/$@

$(OBJECTS) : | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

.PHONY : clean cleanall
clean:
	rm -fr obj *~ engine

cleanall: clean
	rm -fr src/*~ include/*~
