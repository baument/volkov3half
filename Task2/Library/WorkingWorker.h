#pragma once
#include "Worker.h"

class WorkingWorker : public Worker
{
public:
    WorkingWorker(const WorkerData& data);
    std::string getStatus() const override;
};
