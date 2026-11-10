#include "Department.h"
#include <stdexcept>

Department::Department(const std::string& name)
    : name_(name)
{
}

void Department::addPosition(const Position& position)
{
    for (const Position& oldPosition : positions_)
    {
        if (oldPosition.getName() == position.getName())
        {
            throw std::invalid_argument("Такая должность уже есть");
        }
    }

    positions_.push_back(position);
}

void Department::addWorker(Worker& worker)
{
    for (const std::reference_wrapper<Worker>& oldWorkerReference : workers_)
    {
        const Worker& oldWorker = oldWorkerReference.get();

        if (oldWorker.getId() == worker.getId() ||
            oldWorker.getPersonnelNumber() == worker.getPersonnelNumber())
        {
            throw std::invalid_argument("Такой работник уже добавлен");
        }
    }

    bool positionExists = false;

    for (const Position& position : positions_)
    {
        if (position.getName() == worker.getPosition())
        {
            positionExists = true;
        }
    }

    if (!positionExists)
    {
        throw std::invalid_argument("Сначала добавьте должность в отдел кадров");
    }

    workers_.push_back(worker);
}

const std::vector<Position>& Department::getPositions() const
{
    return positions_;
}

WorkerList Department::getWorkers() const
{
    return getAllWorkers();
}

WorkerList Department::getAllWorkers() const
{
    WorkerList result;

    for (const std::reference_wrapper<Worker>& worker : workers_)
    {
        result.push_back(worker.get());
    }

    return result;
}

WorkerList Department::findWorkersByName(const std::string& name) const
{
    WorkerList result;

    for (const std::reference_wrapper<Worker>& workerReference : workers_)
    {
        const Worker& worker = workerReference.get();

        if (worker.getFullName() == name)
        {
            result.push_back(worker);
        }
    }

    return result;
}

WorkerList Department::findWorkersByPosition(const std::string& position) const
{
    WorkerList result;

    for (const std::reference_wrapper<Worker>& workerReference : workers_)
    {
        const Worker& worker = workerReference.get();

        if (worker.getPosition() == position)
        {
            result.push_back(worker);
        }
    }

    return result;
}

WorkerList Department::findWorkersByRate(double rate) const
{
    WorkerList result;

    for (const std::reference_wrapper<Worker>& workerReference : workers_)
    {
        const Worker& worker = workerReference.get();

        if (worker.getRate() == rate)
        {
            result.push_back(worker);
        }
    }

    return result;
}

WorkerList Department::findWorkersWithChildren() const
{
    WorkerList result;

    for (const std::reference_wrapper<Worker>& workerReference : workers_)
    {
        const Worker& worker = workerReference.get();

        if (worker.hasChildren())
        {
            result.push_back(worker);
        }
    }

    return result;
}

WorkerList Department::findPensioners() const
{
    WorkerList result;

    for (const std::reference_wrapper<Worker>& workerReference : workers_)
    {
        const Worker& worker = workerReference.get();

        if (worker.isPensioner())
        {
            result.push_back(worker);
        }
    }

    return result;
}

WorkerList Department::findWorkersWithDisability() const
{
    WorkerList result;

    for (const std::reference_wrapper<Worker>& workerReference : workers_)
    {
        const Worker& worker = workerReference.get();

        if (worker.hasDisability())
        {
            result.push_back(worker);
        }
    }

    return result;
}

WorkerList Department::findWorkersByStatus(const std::string& status) const
{
    WorkerList result;

    for (const std::reference_wrapper<Worker>& workerReference : workers_)
    {
        const Worker& worker = workerReference.get();

        if (worker.getStatus() == status)
        {
            result.push_back(worker);
        }
    }

    return result;
}

const Worker& Department::findWorkerByNumber(const std::string& personnelNumber) const
{
    for (const std::reference_wrapper<Worker>& workerReference : workers_)
    {
        const Worker& worker = workerReference.get();

        if (worker.getPersonnelNumber() == personnelNumber)
        {
            return worker;
        }
    }

    throw std::out_of_range("Работник не найден");
}

std::string Department::toString() const
{
    return name_ + ". Количество работников: " +
           std::to_string(workers_.size());
}
