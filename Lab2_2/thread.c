#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "../Libs/logger.h"

int main() {
    // Инициализация логгера
    initialize_logger();

    // Создание первого потока с приоритетом 7 и алгоритмом FIFO
    pid_t pid1 = fork();
    if (pid1 == -1) { 
        perror("Ошибка при создании первого процесса");
        destroy_logger();
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) { 
        // Дочерний процесс
        setpriority(PRIO_PROCESS, 0, 7); // Установка приоритета 7
        log_message(__FILE__, __LINE__, "Дочерний процесс 1 создан. Приоритет: 7. Алгоритм: FIFO");
        exit(EXIT_SUCCESS); // Выход из дочернего процесса
    } 

    // Создание второго потока с приоритетом 8 и алгоритмом RR
    pid_t pid2 = fork();
    if (pid2 == -1) { 
        perror("Ошибка при создании второго процесса");
        destroy_logger();
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) { 
        // Дочерний процесс
        setpriority(PRIO_PROCESS, 0, 8); // Установка приоритета 8
        log_message(__FILE__, __LINE__, "Дочерний процесс 2 создан. Приоритет: 8. Алгоритм: RR");
        exit(EXIT_SUCCESS); // Выход из дочернего процесса
    } 
    
    // Родительский процесс
    char log_message_buffer[256];
    sprintf(log_message_buffer, "Родительский процесс создан. PID дочернего процесса 1: %d", pid1);
    log_message(__FILE__, __LINE__, log_message_buffer);

    sprintf(log_message_buffer, "Родительский процесс создан. PID дочернего процесса 2: %d", pid2);
    log_message(__FILE__, __LINE__, log_message_buffer);

    destroy_logger();

    return 0;
}


