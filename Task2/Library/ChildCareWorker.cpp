#include "ChildCareWorker.h"

ChildCareWorker::ChildCareWorker(const WorkerData& data)
    : Worker(data)
{
}

std::string ChildCareWorker::getStatus() const
{
    return "В отпуске по уходу за ребёнком";
}
