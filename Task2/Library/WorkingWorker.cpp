#include "WorkingWorker.h"
WorkingWorker::WorkingWorker(const WorkerData &data) : Worker(data, WorkerStatus::Working) {}
std::string WorkingWorker::getStatus() const { return "Работает"; }
