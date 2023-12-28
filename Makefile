CC := g++
CFLAGS := -Wall -std=c++17
LDFLAGS :=

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
STABLE_DIR := stable

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
EXECUTABLE := $(BIN_DIR)/calcula.tor

.PHONY: all clean run ship clean_stable

all: clean $(EXECUTABLE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*

run: $(EXECUTABLE)
	./$(EXECUTABLE)

ship: $(EXECUTABLE) clean_stable
	@mkdir -p $(STABLE_DIR)
	cp $(EXECUTABLE) $(STABLE_DIR)/

clean_stable:
	rm -f $(STABLE_DIR)/*
