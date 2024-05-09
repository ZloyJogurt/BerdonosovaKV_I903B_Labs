CC = gcc
CFLAGS = -Wall -Wextra
INCLUDES = -I../Labs/Libs

EXECUTABLE = program

SRC = process.c
OBJ = $(SRC:.c=.o)

# Добавляем путь к файлам логгера
LOGGER_DIR = ../Libs
LOGGER_SRC = $(LOGGER_DIR)/logger.c
LOGGER_OBJ = $(LOGGER_SRC:.c=.o)

all: $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(EXECUTABLE): $(OBJ) $(LOGGER_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE) $(LOGGER_OBJ)
