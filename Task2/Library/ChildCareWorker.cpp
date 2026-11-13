#include "ChildCareWorker.h"

// Создаём сотрудника в отпуске по уходу за ребёнком.
ChildCareWorker::ChildCareWorker(const WorkerData &data) : Worker(data, WorkerStatus::ChildCare) {}

// Возвращаем текст статуса отпуска по уходу.
std::string ChildCareWorker::getStatus() const { return "В отпуске по уходу за ребёнком"; }
