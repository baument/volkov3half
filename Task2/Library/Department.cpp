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

void Department::addWorker(Worker* worker)
{
    if (worker == nullptr)
    {
        throw std::invalid_argument("Работник не задан");
    }

    for (const Worker* oldWorker : workers_)
    {
        if (oldWorker->getId() == worker->getId() ||
            oldWorker->getPersonnelNumber() == worker->getPersonnelNumber())
        {
            throw std::invalid_argument("Такой работник уже добавлен");
        }
    }

    bool positionExists = false;

    for (const Position& position : positions_)
    {
        if (position.getName() == worker->getPosition())
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

const std::vector<Worker*>& Department::getWorkers() const
{
    return workers_;
}

std::vector<const Worker*> Department::getAllWorkers() const
{
    std::vector<const Worker*> result;

    for (const Worker* worker : workers_)
    {
        result.push_back(worker);
    }

    return result;
}

std::vector<const Worker*> Department::findWorkersByName(const std::string& name) const
{
    std::vector<const Worker*> result;

    for (const Worker* worker : workers_)
    {
        if (worker->getFullName() == name)
        {
            result.push_back(worker);
        }
    }

    return result;
}

std::vector<const Worker*> Department::findWorkersByPosition(const std::string& position) const
{
    std::vector<const Worker*> result;

    for (const Worker* worker : workers_)
    {
        if (worker->getPosition() == position)
        {
            result.push_back(worker);
        }
    }

    return result;
}

std::vector<const Worker*> Department::findWorkersByRate(double rate) const
{
    std::vector<const Worker*> result;

    for (const Worker* worker : workers_)
    {
        if (worker->getRate() == rate)
        {
            result.push_back(worker);
        }
    }

    return result;
}

std::vector<const Worker*> Department::findWorkersWithChildren() const
{
    std::vector<const Worker*> result;

    for (const Worker* worker : workers_)
    {
        if (worker->hasChildren())
        {
            result.push_back(worker);
        }
    }

    return result;
}

std::vector<const Worker*> Department::findPensioners() const
{
    std::vector<const Worker*> result;

    for (const Worker* worker : workers_)
    {
        if (worker->isPensioner())
        {
            result.push_back(worker);
        }
    }

    return result;
}

std::vector<const Worker*> Department::findWorkersWithDisability() const
{
    std::vector<const Worker*> result;

    for (const Worker* worker : workers_)
    {
        if (worker->hasDisability())
        {
            result.push_back(worker);
        }
    }

    return result;
}

std::vector<const Worker*> Department::findWorkersByStatus(const std::string& status) const
{
    std::vector<const Worker*> result;

    for (const Worker* worker : workers_)
    {
        if (worker->getStatus() == status)
        {
            result.push_back(worker);
        }
    }

    return result;
}

const Worker* Department::findWorkerByNumber(const std::string& personnelNumber) const
{
    for (const Worker* worker : workers_)
    {
        if (worker->getPersonnelNumber() == personnelNumber)
        {
            return worker;
        }
    }

    return nullptr;
}

std::string Department::toString() const
{
    return name_ + ". Количество работников: " +
           std::to_string(workers_.size());
}
