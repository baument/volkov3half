#pragma once
#include "Worker.h"
class WorkingWorker : public Worker { public: explicit WorkingWorker(const WorkerData& data); std::string getStatus() const override; };
