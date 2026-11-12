#include "VacationWorker.h"
VacationWorker::VacationWorker(const WorkerData &data) : Worker(data, WorkerStatus::Vacation) {}
std::string VacationWorker::getStatus() const { return "В очередном отпуске"; }
