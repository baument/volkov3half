#pragma once
#include "Worker.h"

class ChildCareWorker : public Worker
{
public:
    ChildCareWorker(const WorkerData& data);
    std::string getStatus() const override;
};
