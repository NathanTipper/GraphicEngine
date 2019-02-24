CXX = g++
CXXFLAGS = -Wall -g

OBJECTS = $(addprefix $(OBJ_DIR)/, main.o)
vpath %.h ./include
vpath %.o ./obj
vpath %.cc ./src

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

$(OBJ_DIR)/%.o : %.cc
	$(CXX) -c $(CXXFLAGS) $^ -o $@

engine: $(OBJECTS)
	@echo Starting installation
	$(CXX) $(CXXFLAGS) -o engine $(OBJECTS)

$(OBJECTS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir obj

.PHONY : clean
clean:
	rm -fr obj *~ engine
