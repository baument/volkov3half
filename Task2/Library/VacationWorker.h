#pragma once
#include "Worker.h"
/**
 * @brief Представляет сотрудника в очередном отпуске.
 *
 * Наследует кадровые данные от Worker и переопределяет текст статуса.
 */
class VacationWorker : public Worker
{
  public:
    /**
     * @brief Создаёт сотрудника в очередном отпуске.
     * @param data Кадровые данные сотрудника.
     * @throws std::invalid_argument Если данные сотрудника некорректны.
     */
    explicit VacationWorker(const WorkerData &data);
    /**
     * @brief Возвращает статус очередного отпуска.
     * @return Строка «В очередном отпуске».
     */
    std::string getStatus() const override;
};
