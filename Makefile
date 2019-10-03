CFLAGS = -ansi -pedantic -Wall -Werror -std=c++11

CC = g++

SRC := src
OBJ := obj
DEBUG := debug
RELEASE := release

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/$(RELEASE)/%.o, $(SOURCES))
OBJECTS_DBG := $(patsubst $(SRC)/%.cpp, $(OBJ)/$(DEBUG)/%.o, $(SOURCES))

release: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

debug: $(OBJECTS_DBG)
	$(CC) -o $@ $^ $(CFLAGS) -g

$(OBJ)/$(RELEASE)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)/$(RELEASE)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/$(DEBUG)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)/$(DEBUG)
	$(CC) -c $< -o $@ $(CFLAGS) -g -D MAP

clean:
	rm obj/*/*.o debug release -f