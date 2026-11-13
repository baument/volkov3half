#pragma once
#include "Worker.h"
/**
 * @brief Представляет сотрудника со статусом работы.
 *
 * Наследует кадровые данные от Worker и переопределяет текст статуса.
 */
class WorkingWorker : public Worker
{
  public:
    /**
     * @brief Создаёт работающего сотрудника.
     * @param data Кадровые данные сотрудника.
     * @throws std::invalid_argument Если данные сотрудника некорректны.
     */
    explicit WorkingWorker(const WorkerData &data);
    /**
     * @brief Возвращает статус работающего сотрудника.
     * @return Строка «Работает».
     */
    std::string getStatus() const override;
};
