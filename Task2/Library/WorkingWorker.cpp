#include "WorkingWorker.h"

// Создаём сотрудника со статусом работы.
WorkingWorker::WorkingWorker(const WorkerData &data) : Worker(data, WorkerStatus::Working) {}

// Возвращаем текст статуса работающего сотрудника.
std::string WorkingWorker::getStatus() const { return "Работает"; }
