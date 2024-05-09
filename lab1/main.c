#include <stdio.h>
#include "logger.h"

// Макрос для удобного использования функции логирования
#define Logger(msg) log_message(__FILE__, __LINE__, msg)

int main() {
    // Инициализируем логгер
    initialize_logger();
    // Пример использования логгера
    Logger("Бердоносова К.В. И903Б");
    // Завершаем работу логгера
    destroy_logger();
    return 0;
}
