#pragma once
#include "Worker.h"
class ChildCareWorker : public Worker
{
  public:
    explicit ChildCareWorker(const WorkerData &data);
    std::string getStatus() const override;
};
