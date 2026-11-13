#include "Department.h"
#include <cmath>
#include <stdexcept>
Department::Department(const std::string &name) : name_(name) {}
void Department::addPosition(const Position &p)
{
    // Проверяем, что должности с таким названием ещё нет.
    for (const Position &x : positions_)
        if (x.getName() == p.getName())
            throw std::invalid_argument("Такая должность уже есть");
    positions_.push_back(p);
}
void Department::addWorker(const WorkerData &d)
{
    // Не допускаем повторный табельный номер.
    for (const Worker &w : workers_)
        if (w.getPersonnelNumber() == d.personnelNumber)
            throw std::invalid_argument("Такой работник уже есть");
    // Ищем должность сотрудника среди должностей отдела.
    bool ok = false;
    for (const Position &p : positions_)
        if (p.getName() == d.position)
            ok = true;
    if (!ok)
        throw std::invalid_argument("Сначала добавьте должность");
    // Создаём полноценный объект Worker внутри vector.
    workers_.emplace_back(d);
}
const std::vector<Position> &Department::getPositions() const { return positions_; }
const std::vector<Worker> &Department::getWorkers() const { return workers_; }
// Общий цикл исключает дублирование логики поиска по сотрудникам.
template <class P> static std::vector<std::size_t> find(const std::vector<Worker> &ws, P p)
{
    std::vector<std::size_t> r;
    for (std::size_t i = 0; i < ws.size(); ++i)
        if (p(ws[i]))
            r.push_back(i);
    return r;
}
std::vector<std::size_t> Department::getAllWorkers() const
{
    return find(workers_, [](const Worker &) { return true; });
}
std::vector<std::size_t> Department::findWorkersByName(const std::string &s) const
{
    return find(workers_, [&](const Worker &w) { return w.getFullName() == s; });
}
std::vector<std::size_t> Department::findWorkersByPosition(const std::string &s) const
{
    return find(workers_, [&](const Worker &w) { return w.getPosition() == s; });
}
std::vector<std::size_t> Department::findWorkersByRate(double x) const
{
    return find(workers_, [&](const Worker &w) { return std::abs(w.getRate() - x) < 1e-9; });
}
std::vector<std::size_t> Department::findWorkersWithChildren() const
{
    return find(workers_, [](const Worker &w) { return w.hasChildren(); });
}
std::vector<std::size_t> Department::findPensioners() const
{
    return find(workers_, [](const Worker &w) { return w.isPensioner(); });
}
std::vector<std::size_t> Department::findWorkersWithDisability() const
{
    return find(workers_, [](const Worker &w) { return w.hasDisability(); });
}
std::vector<std::size_t> Department::findWorkersByStatus(WorkerStatus s) const
{
    return find(workers_, [&](const Worker &w) { return w.getWorkerStatus() == s; });
}
const Worker &Department::findWorkerByNumber(const std::string &s) const
{
    for (const Worker &w : workers_)
        if (w.getPersonnelNumber() == s)
            return w;
    throw std::out_of_range("Работник не найден");
}
std::string Department::toString() const
{
    return name_ + ". Количество работников: " + std::to_string(workers_.size());
}
