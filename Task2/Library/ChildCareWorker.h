#pragma once
#include "Worker.h"
// Сотрудник в отпуске по уходу за ребёнком.
class ChildCareWorker : public Worker
{
  public:
    // Создаёт сотрудника в отпуске по уходу за ребёнком.
    explicit ChildCareWorker(const WorkerData &data);
    // Возвращает статус отпуска по уходу.
    std::string getStatus() const override;
};
