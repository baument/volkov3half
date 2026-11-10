#pragma once
#include "Worker.h"

class VacationWorker : public Worker
{
public:
    VacationWorker(const WorkerData& data);
    std::string getStatus() const override;
};
