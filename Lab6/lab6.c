#include <stdio.h>
#include <pthread.h>
#include "../Libs/logger.h"

// Глобальные переменные для синхронизации между производителем и потребителем
int data_ready = 0; // Флаг, указывающий, что данные готовы к чтению
int inf = 0; // Данные, которые производит производитель
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Мьютекс для обеспечения критической секции
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER; // Условная переменная для сигнализации между производителем и потребителем
int quit = 0; // Флаг для завершения потоков

// Потребитель - функция, которая читает данные
void* consumer(void* not_used)
{
    while(!quit)
    {
        pthread_mutex_lock(&mutex); // Захватываем мьютекс для входа в критическую секцию
        char log_message_buffer[256]; // Буфер для хранения сообщения
        log_message(__FILE__, __LINE__, "CONSUMER: W1"); // Логируем состояние
        while(!data_ready) // Ждем, пока данные не будут готовы
        {
            log_message(__FILE__, __LINE__, "CONSUMER: W2"); // Логируем состояние
            pthread_cond_wait(&condvar, &mutex); // Ожидаем сигнала о готовности данных
            log_message(__FILE__, __LINE__, "CONSUMER: W3"); // Логируем состояние
        }
        sprintf(log_message_buffer, "CONSUMER: Полученные потребителем данные = %d ", inf); // Формируем сообщение о полученных данных
        log_message(__FILE__, __LINE__, log_message_buffer); // Логируем полученные данные
        data_ready = 0; // Сбрасываем флаг готовности данных
        pthread_cond_signal(&condvar); // Сигнализируем производителю, что данные прочитаны
        pthread_mutex_unlock(&mutex); // Освобождаем мьютекс
    }
}

// Производитель - функция, которая записывает данные
void* producer(void* not_used)
{
    while(!quit)
    {
        sleep(1); // Имитируем задержку для получения данных от устройства
        char log_message_buffer[256]; // Буфер для хранения сообщения
        sprintf(log_message_buffer, "PRODUCER: Полученные производителем данные от h/w = %d ", inf); // Формируем сообщение о полученных данных
        log_message(__FILE__, __LINE__, log_message_buffer); // Логируем полученные данные
        pthread_mutex_lock(&mutex); // Захватываем мьютекс для входа в критическую секцию
        log_message(__FILE__, __LINE__, "PRODUCER: WP1"); // Логируем состояние
        while(data_ready) // Ждем, пока данные не будут обработаны
        {
            log_message(__FILE__, __LINE__, "PRODUCER: WP2"); // Логируем состояние
            pthread_cond_wait(&condvar, &mutex); // Ожидаем сигнала о готовности обработки данных
        }
        data_ready = 1; // Устанавливаем флаг готовности данных
        inf++; // Увеличиваем значение данных
        log_message(__FILE__, __LINE__, "PRODUCER: WP3"); // Логируем состояние
        pthread_cond_signal(&condvar); // Сигнализируем потребителю о готовности данных
        pthread_mutex_unlock(&mutex); // Освобождаем мьютекс
    }
}

void main()
{
    initialize_logger(); // Инициализируем логгер
    log_message(__FILE__, __LINE__, "Start"); // Логируем начало выполнения программы

    pthread_t consumer_id, producer_id; // Идентификаторы потоков потребителя и производителя
    pthread_create(&consumer_id, NULL, consumer, NULL); // Создаем поток потребителя
    pthread_create(&producer_id, NULL, producer, NULL); // Создаем поток производителя

    sleep(3); // Ждем 3 секунды
    quit++; // Устанавливаем флаг завершения потоков

    pthread_join(consumer_id, NULL); // Ожидаем завершения потока потребителя
    pthread_join(producer_id, NULL); // Ожидаем завершения потока производителя

    destroy_logger(); // Уничтожаем логгер
}

