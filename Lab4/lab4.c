#include <stdio.h>
#include <time.h>
#include <sync.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/neutrino.h>
#include "../Libs/logger.h"

barrier_t barrier; // Объявление глобальной переменной для барьера

void *thread1(void * not_used)
{
    log_message(__FILE__, __LINE__, "Начало ожидания барьера в 1 потоке"); // Запись сообщения о начале ожидания барьера
    sleep(1); // Задержка на 1 секунду
    barrier_wait(&barrier); // Ожидание барьера
    log_message(__FILE__, __LINE__, "Окончание ожидания барьера в 1 потоке"); // Запись сообщения об окончании ожидания барьера
}

void *thread2(void * not_used)
{
    log_message(__FILE__, __LINE__, "Начало ожидания барьера в 2 потоке"); // Запись сообщения о начале ожидания барьера
    sleep(2); // Задержка на 2 секунды
    barrier_wait(&barrier); // Ожидание барьера
    log_message(__FILE__, __LINE__, "Окончание ожидания барьера в 2 потоке"); // Запись сообщения об окончании ожидания барьера
}


int main()
{
    initialize_logger(); // Инициализация логгера

    int NUM_THREADS = 2; // Количество потоков
    pthread_t t1; // Переменная для идентификатора первого потока
    pthread_t t2; // Переменная для идентификатора второго потока

    barrier_init(&barrier, NULL, NUM_THREADS + 1); // Инициализация барьера

    log_message(__FILE__, __LINE__, "Запуск программы"); // Запись сообщения о запуске программы в лог

    pthread_create(&t1, NULL, thread1, NULL); // Создание первого потока
    pthread_create(&t2, NULL, thread2, NULL); // Создание второго потока

    log_message(__FILE__, __LINE__, "Начало ожидания барьера в main"); // Запись сообщения о начале ожидания барьера в функции main
    barrier_wait(&barrier); // Ожидание барьера в функции main
    log_message(__FILE__, __LINE__, "Окончание ожидания барьера в main"); // Запись сообщения об окончании ожидания барьера в функции main

    pthread_join(t1, NULL); // Ожидание завершения первого потока
    pthread_join(t2, NULL); // Ожидание завершения второго потока

    destroy_logger(); // Завершение работы с логгером

    return 0;
}
