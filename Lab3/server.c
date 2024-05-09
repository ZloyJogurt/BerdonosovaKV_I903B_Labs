#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <string.h> 
#include <unistd.h>
#include "../Libs/logger.h"

// Функция сервера, обрабатывающая запросы от клиентов
void server(void) {
    int rcvid; // Идентификатор сообщения
    int chid; // Идентификатор канала
    char message[256]; // Буфер для принимаемого сообщения
    char response[512]; // Буфер для отправляемого ответа
    char log_message_buffer[256]; // Буфер для хранения сообщения для логгера
    log_message(__FILE__, __LINE__, "Сервер"); // Запись сообщения о запуске сервера в лог

    chid = ChannelCreate(0); // Создание канала для обмена сообщениями
    sprintf(log_message_buffer, "id канала: = %d", chid); // Форматирование строки для логгера с информацией об идентификаторе канала
    log_message(__FILE__, __LINE__, log_message_buffer); // Запись сообщения о создании канала в лог

    sprintf(log_message_buffer, "PID: = %d", getpid()); // Форматирование строки для логгера с информацией о PID сервера
    log_message(__FILE__, __LINE__, log_message_buffer); // Запись сообщения о PID сервера в лог

    while (1) {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL); // Получение сообщения от клиента
        sprintf(log_message_buffer, "Полученное сервером сообщение: = %s", message); // Форматирование строки для логгера с принятым сообщением
        log_message(__FILE__, __LINE__, log_message_buffer); // Запись сообщения о принятом сообщении в лог

        snprintf(response, sizeof(response), "Это ответ сервера на сообщение '%s'", message); // Формирование ответа сервера
        MsgReply(rcvid, EOK, response, sizeof(response)); // Отправка ответа клиенту
        sprintf(log_message_buffer, "Отправленное сервером сообщение: = %s", response); // Форматирование строки для логгера с отправленным сообщением
        log_message(__FILE__, __LINE__, log_message_buffer); // Запись сообщения о отправленном сообщении в лог
    }
}

int main(void) {
    initialize_logger(); // Инициализация логгера
    server(); // Запуск сервера
    destroy_logger(); // Завершение работы с логгером
    return 0; 
}

