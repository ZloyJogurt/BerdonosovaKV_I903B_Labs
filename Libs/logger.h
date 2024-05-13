#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

// Объявление функций логгера
void initialize_logger();
void log_message(const char *filename, int line, const char *message);
void destroy_logger();

#endif /* LOGGER_H */