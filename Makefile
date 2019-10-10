CFLAGS = -ansi -pedantic -Wall -Werror -std=c++11

CC = g++

SRC := src
OBJ := obj
DEBUG := debug
RELEASE := release

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/$(RELEASE)/%.o, $(SOURCES))
OBJECTS_DBG := $(patsubst $(SRC)/%.cpp, $(OBJ)/$(DEBUG)/%.o, $(SOURCES))

# executable sans option de debug
release: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

# executable avec options de debug + definition de la constante MAP
debug: $(OBJECTS_DBG)
	$(CC) -o $@ $^ $(CFLAGS) -g -D MAP

$(OBJ)/$(RELEASE)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)/$(RELEASE)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/$(DEBUG)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)/$(DEBUG)
	$(CC) -c $< -o $@ $(CFLAGS) -g -D MAP

clean:
	rm obj/*/*.o debug release *_test -f
