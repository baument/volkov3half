#pragma once
#include "Position.h"
#include "Worker.h"
#include <cstddef>
#include <string>
#include <vector>
// Номера сотрудников в хранилище отдела.
using WorkerIndices = std::vector<std::size_t>;
// Отдел кадров хранит должности и сотрудников по значению.
class Department
{
    std::string name_;
    std::vector<Position> positions_;
    std::vector<Worker> workers_;

  public:
    // Создаёт отдел с указанным названием.
    explicit Department(const std::string &name);
    // Добавляет должность после проверки дубликата.
    void addPosition(const Position &position);
    // Создаёт и добавляет сотрудника по его данным.
    void addWorker(const WorkerData &data);
    // Возвращает сохранённые должности.
    const std::vector<Position> &getPositions() const;
    // Возвращает сохранённых сотрудников.
    const std::vector<Worker> &getWorkers() const;
    // Возвращает индексы всех сотрудников.
    std::vector<std::size_t> getAllWorkers() const;
    // Ищет сотрудников по ФИО.
    std::vector<std::size_t> findWorkersByName(const std::string &) const;
    // Ищет сотрудников по должности.
    std::vector<std::size_t> findWorkersByPosition(const std::string &) const;
    // Ищет сотрудников по ставке.
    std::vector<std::size_t> findWorkersByRate(double) const;
    // Ищет сотрудников с детьми.
    std::vector<std::size_t> findWorkersWithChildren() const;
    // Ищет сотрудников-пенсионеров.
    std::vector<std::size_t> findPensioners() const;
    // Ищет сотрудников с инвалидностью.
    std::vector<std::size_t> findWorkersWithDisability() const;
    // Ищет сотрудников по статусу.
    std::vector<std::size_t> findWorkersByStatus(WorkerStatus) const;
    // Ищет сотрудника по номеру или выбрасывает исключение.
    const Worker &findWorkerByNumber(const std::string &) const;
    // Возвращает краткую информацию об отделе.
    std::string toString() const;
};
