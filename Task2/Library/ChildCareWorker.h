#pragma once
#include "Worker.h"
/**
 * @brief Представляет сотрудника в отпуске по уходу за ребёнком.
 *
 * Наследует кадровые данные от Worker и переопределяет текст статуса.
 */
class ChildCareWorker : public Worker
{
  public:
    /**
     * @brief Создаёт сотрудника в отпуске по уходу за ребёнком.
     * @param data Кадровые данные сотрудника.
     * @throws std::invalid_argument Если данные сотрудника некорректны.
     */
    explicit ChildCareWorker(const WorkerData &data);
    /**
     * @brief Возвращает статус отпуска по уходу за ребёнком.
     * @return Строка с текстом статуса отпуска.
     */
    std::string getStatus() const override;
};
