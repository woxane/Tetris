# Makefile

CXX = g++
CXXFLAGS = -std=c++11
SRC_FILES = main.cpp game.cpp screen.cpp utils.cpp
TARGET = tetris 

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)

