#include "ChildCareWorker.h"
ChildCareWorker::ChildCareWorker(const WorkerData &data) : Worker(data, WorkerStatus::ChildCare) {}
std::string ChildCareWorker::getStatus() const { return "В отпуске по уходу за ребёнком"; }
