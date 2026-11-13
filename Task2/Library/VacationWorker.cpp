#include "VacationWorker.h"

// Создаём сотрудника со статусом очередного отпуска.
VacationWorker::VacationWorker(const WorkerData &data) : Worker(data, WorkerStatus::Vacation) {}

// Возвращаем текст статуса отпуска.
std::string VacationWorker::getStatus() const { return "В очередном отпуске"; }
