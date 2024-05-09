CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -o program main.c logger.c
SRC_DIR = src
BUILD_DIR = build
EXECUTABLE = program
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean

all: $(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)
