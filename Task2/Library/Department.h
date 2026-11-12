#pragma once
#include "Position.h"
#include "Worker.h"
#include <cstddef>
#include <string>
#include <vector>
using WorkerIndices = std::vector<std::size_t>;
class Department { std::string name_; std::vector<Position> positions_; std::vector<Worker> workers_; public: explicit Department(const std::string& name); void addPosition(const Position& position); void addWorker(const WorkerData& data); const std::vector<Position>& getPositions() const; const std::vector<Worker>& getWorkers() const; std::vector<std::size_t> getAllWorkers() const; std::vector<std::size_t> findWorkersByName(const std::string&) const; std::vector<std::size_t> findWorkersByPosition(const std::string&) const; std::vector<std::size_t> findWorkersByRate(double) const; std::vector<std::size_t> findWorkersWithChildren() const; std::vector<std::size_t> findPensioners() const; std::vector<std::size_t> findWorkersWithDisability() const; std::vector<std::size_t> findWorkersByStatus(WorkerStatus) const; const Worker& findWorkerByNumber(const std::string&) const; std::string toString() const; };
