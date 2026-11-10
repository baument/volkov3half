#pragma once
#include "Position.h"
#include "Worker.h"
#include <string>
#include <vector>

class Department
{
private:
    std::string name_;
    std::vector<Position> positions_;
    std::vector<Worker*> workers_;

public:
    Department(const std::string& name);

    void addPosition(const Position& position);
    void addWorker(Worker* worker);

    const std::vector<Position>& getPositions() const;
    const std::vector<Worker*>& getWorkers() const;
    std::vector<const Worker*> getAllWorkers() const;

    std::vector<const Worker*> findWorkersByName(const std::string& name) const;
    std::vector<const Worker*> findWorkersByPosition(const std::string& position) const;
    std::vector<const Worker*> findWorkersByRate(double rate) const;
    std::vector<const Worker*> findWorkersWithChildren() const;
    std::vector<const Worker*> findPensioners() const;
    std::vector<const Worker*> findWorkersWithDisability() const;
    std::vector<const Worker*> findWorkersByStatus(const std::string& status) const;

    const Worker* findWorkerByNumber(const std::string& personnelNumber) const;
    std::string toString() const;
};
