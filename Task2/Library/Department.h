#pragma once
#include "Position.h"
#include "Worker.h"
#include <functional>
#include <string>
#include <vector>

using WorkerList = std::vector<std::reference_wrapper<const Worker>>;

class Department
{
private:
    std::string name_;
    std::vector<Position> positions_;
    std::vector<std::reference_wrapper<Worker>> workers_;

public:
    Department(const std::string& name);

    void addPosition(const Position& position);
    void addWorker(Worker& worker);

    const std::vector<Position>& getPositions() const;
    WorkerList getWorkers() const;
    WorkerList getAllWorkers() const;

    WorkerList findWorkersByName(const std::string& name) const;
    WorkerList findWorkersByPosition(const std::string& position) const;
    WorkerList findWorkersByRate(double rate) const;
    WorkerList findWorkersWithChildren() const;
    WorkerList findPensioners() const;
    WorkerList findWorkersWithDisability() const;
    WorkerList findWorkersByStatus(const std::string& status) const;

    const Worker& findWorkerByNumber(const std::string& personnelNumber) const;
    std::string toString() const;
};
