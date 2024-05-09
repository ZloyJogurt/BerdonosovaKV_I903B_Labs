#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <string.h> 
#include <unistd.h>
#include "../Libs/logger.h"

int main(void) {
    initialize_logger(); // Инициализация логгера

    char smsg[100]; // Буфер для вводимого сообщения
    char rmsg[200]; // Буфер для принимаемого сообщения
    int coid; // Идентификатор соединения
    long serv_pid; // PID сервера
    char log_message_buffer[256]; // Буфер для хранения сообщения для логгера

    log_message(__FILE__, __LINE__, "Клиент"); // Запись сообщения о запуске клиента в лог
    sleep(1); // Задержка на 1 секунду для ожидания инициализации

    printf("Введите PID сервера:\n"); // Вывод на экран запроса PID сервера
    scanf("%ld", &serv_pid); // Считывание PID сервера
    getchar(); // Считывание символа новой строки, оставшегося после ввода PID

    coid = ConnectAttach(0, serv_pid, 1, 0, 0); // Подключение к серверу по его PID
    sprintf(log_message_buffer, "coid = %d", coid); // Форматирование строки для логгера с информацией об идентификаторе соединения
    log_message(__FILE__, __LINE__, log_message_buffer); // Запись сообщения о создании соединения в лог

    while (1) {
        sleep(1); // Задержка на 1 секунду перед каждым запросом
        printf("\nВведите сообщение (для выхода введите 'exit'):\n"); // Вывод на экран приглашения для ввода сообщения
        fgets(smsg, sizeof(smsg), stdin); // Получение сообщения от пользователя

        if (!strcmp(smsg, "exit\n")) { // Проверка на выход
            ConnectDetach(coid); // Отключение от сервера
            destroy_logger(); // Завершение работы с логгером
            exit(0); // Выход из программы
        }

        size_t len = strlen(smsg); // Вычисление длины введенного сообщения
        if (len > 0 && smsg[len - 1] != '\0') { // Проверка на наличие завершающего нуля
            smsg[len - 1] = '\0'; // Добавление завершающего нуля, если он отсутствует
        }

        snprintf(log_message_buffer, sizeof(log_message_buffer), "Введенное сообщение: %s", smsg); // Форматирование строки для логгера с информацией о введенном сообщении
        log_message(__FILE__, __LINE__, log_message_buffer); // Запись сообщения о введенном сообщении в лог

        if (MsgSend(coid, smsg, strlen(smsg) + 1, rmsg, sizeof(rmsg)) == -1) { // Отправка сообщения серверу и проверка на ошибку
            ConnectDetach(coid); // Отключение от сервера
            destroy_logger(); // Завершение работы с логгером
            log_message(__FILE__, __LINE__, "Ошибка отправки сообщения"); // Запись сообщения об ошибке в лог
            return 1; // Возврат кода ошибки
        }

        snprintf(log_message_buffer, sizeof(log_message_buffer), "Полученное сообщение: %s", rmsg); // Форматирование строки для логгера с информацией о принятом сообщении
        log_message(__FILE__, __LINE__, log_message_buffer); // Запись сообщения о принятом сообщении в лог
    }

    ConnectDetach(coid); // Отключение от сервера
    destroy_logger(); // Завершение работы с логгером
    return 0;
}
