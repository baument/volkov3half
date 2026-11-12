#pragma once
#include "Worker.h"
class VacationWorker : public Worker { public: explicit VacationWorker(const WorkerData& data); std::string getStatus() const override; };
