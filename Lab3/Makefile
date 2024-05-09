CC = gcc
CFLAGS = -Wall -Wextra
INCLUDES = -I../Labs/Libs

CLIENT_EXECUTABLE = client
SERVER_EXECUTABLE = server

SRC_CLIENT = client.c
SRC_SERVER = server.c

# Добавляем путь к файлам логгера
LOGGER_DIR = ../Libs
LOGGER_SRC = $(LOGGER_DIR)/logger.c
LOGGER_OBJ = $(LOGGER_SRC:.c=.o)

all: $(CLIENT_EXECUTABLE) $(SERVER_EXECUTABLE)

$(CLIENT_EXECUTABLE): $(SRC_CLIENT) $(LOGGER_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(SERVER_EXECUTABLE): $(SRC_SERVER) $(LOGGER_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

clean:
	rm -f $(CLIENT_EXECUTABLE) $(SERVER_EXECUTABLE) $(LOGGER_OBJ)

