#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../Libs/logger.h"

int main() {
    initialize_logger();

    pid_t pid = fork(); // Создание дочернего процесса

    if (pid == -1) { // Проверка на ошибку
        perror("Ошибка при создании процесса");
        destroy_logger();
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Дочерний процесс
        char log_message_buffer[256]; // Буфер для хранения сообщения
        sprintf(log_message_buffer, "Дочерний процесс: pid = %d, ppid = %d", getpid(), getppid());
        log_message(__FILE__, __LINE__, log_message_buffer);
    } else { // Родительский процесс
        int status;
        wait(&status); // Ожидание завершения дочернего процесса
        char log_message_buffer[256];
        sprintf(log_message_buffer, "Родительский процесс: pid = %d", getpid());
        log_message(__FILE__, __LINE__, log_message_buffer);
    }
    destroy_logger();
    return 0;
}
