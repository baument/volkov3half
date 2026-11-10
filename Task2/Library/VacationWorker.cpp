#include "VacationWorker.h"

VacationWorker::VacationWorker(const WorkerData& data)
    : Worker(data)
{
}

std::string VacationWorker::getStatus() const
{
    return "В очередном отпуске";
}
