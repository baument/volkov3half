#pragma once
#include "Worker.h"
// Сотрудник со статусом работы.
class WorkingWorker : public Worker
{
  public:
    // Создаёт работающего сотрудника.
    explicit WorkingWorker(const WorkerData &data);
    // Возвращает статус работающего сотрудника.
    std::string getStatus() const override;
};
