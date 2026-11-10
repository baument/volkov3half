#include "WorkingWorker.h"

WorkingWorker::WorkingWorker(const WorkerData& data)
    : Worker(data)
{
}

std::string WorkingWorker::getStatus() const
{
    return "Работает";
}
