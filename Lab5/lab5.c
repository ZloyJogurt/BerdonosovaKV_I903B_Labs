#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include "../Libs/logger.h"

#define SEC_NSEC 1000000000LL // Макрос для преобразования секунд в наносекунды

void *long_thread(void *notused) {
    char buffer[256]; // Буфер для хранения сообщения
    int time = 20; // Время выполнения потока в секундах
    (void)notused; // Используем notused, чтобы подавить предупреждение о неиспользованной переменной
    sprintf(buffer, "Поток будет выполняться %d секунд", time); // Форматируем сообщение о времени выполнения потока
    log_message(__FILE__, __LINE__, buffer); // Записываем сообщение в лог
    sleep(time); // Засыпаем на указанное время
    return NULL; // Возвращаем NULL
}

int main(void)
{
    initialize_logger(); // Инициализируем логгер

    char log_message_buffer[256]; // Буфер для хранения сообщения
    uint64_t timeout; // Переменная для хранения времени ожидания
    struct sigevent event; // Структура для описания события
    int rval; // Переменная для хранения результата операции
    pthread_t thread_id; // Идентификатор потока

    log_message(__FILE__, __LINE__, "Программа запустилась"); // Записываем сообщение о запуске программы в лог

    event.sigev_notify = SIGEV_UNBLOCK; // Устанавливаем уведомление о событии "разблокирование"
    pthread_create(&thread_id, NULL, long_thread, NULL); // Создаем поток для выполнения long_thread

    timeout = 10LL * SEC_NSEC; // Устанавливаем время ожидания в 10 секунд
    TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL); // Устанавливаем таймер ожидания завершения потока
    rval = pthread_join(thread_id, NULL); // Ждем завершения потока
    if (rval == ETIMEDOUT) // Если время ожидания истекло
    {
        snprintf(log_message_buffer, sizeof(log_message_buffer), "Поток %" PRIuPTR " выполняется более 10 секунд", (uintptr_t)thread_id); // Форматируем сообщение о превышении времени выполнения
        log_message(__FILE__, __LINE__, log_message_buffer); // Записываем сообщение в лог
    }
    else // Если поток завершился до истечения времени ожидания
    {
        snprintf(log_message_buffer, sizeof(log_message_buffer), "Поток %" PRIuPTR " завершился до таймаута", (uintptr_t)thread_id); // Форматируем сообщение о завершении потока
        log_message(__FILE__, __LINE__, log_message_buffer); // Записываем сообщение в лог
    }

    destroy_logger(); // Завершаем работу с логгером

    return 0; // Возвращаем успешное завершение программы
}
