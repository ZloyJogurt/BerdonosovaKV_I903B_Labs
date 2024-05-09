#include "logger.h"
#include <stdlib.h>
#include <time.h>

// Статическая переменная для хранения указателя на файл лога
static FILE *log_file = NULL;

// Функция инициализации логгера
void initialize_logger() {
    // Открываем файл для записи лога
    log_file = fopen("log.txt", "w");
    // Проверяем успешность открытия файла
    if (!log_file) {
        // Если произошла ошибка, выводим сообщение об ошибке и завершаем программу
        perror("Ошибка при открытии файла лога");
        exit(EXIT_FAILURE);
    }
}

// Функция записи сообщения в лог
void log_message(const char *filename, int line, const char *message) {
    // Получаем текущее время
    time_t current_time = time(NULL);
    struct tm *timeinfo = localtime(&current_time);
    
    // Записываем сообщение в файл лога с указанием времени, имени файла, номера строки и текста сообщения
    fprintf(log_file, "[%d-%d-%d %d:%d:%d %s:%d] %s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, filename, line, message);
    // Принудительно записываем данные на диск
    fflush(log_file);
    // Выводим сообщение также в консоль для отображения в реальном времени
    printf("[%d-%d-%d %d:%d:%d %s:%d] %s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, filename, line, message);
}

// Функция закрытия файла лога
void destroy_logger() {
    // Проверяем, открыт ли файл лога
    if (log_file) {
        // Если да, закрываем его
        fclose(log_file);
        // Устанавливаем указатель на файл в NULL, чтобы избежать ошибок при повторном использовании логгера
        log_file = NULL;
    }
}