#pragma once
#include "Worker.h"
// Сотрудник в очередном отпуске.
class VacationWorker : public Worker
{
  public:
    // Создаёт сотрудника в очередном отпуске.
    explicit VacationWorker(const WorkerData &data);
    // Возвращает статус отпуска.
    std::string getStatus() const override;
};
