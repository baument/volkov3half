#pragma once
#include "Person.h"
#include <string>
#include <vector>
// Возможные статусы сотрудника.
enum class WorkerStatus
{
    Working,
    Vacation,
    ChildCare
};
// Набор данных для создания сотрудника.
struct WorkerData
{
    std::string fullName, personnelNumber, position;
    double rate = 1.0;
    bool hasChildren = false, isPensioner = false, hasDisability = false;
    std::vector<std::string> previousJobs;
    WorkerStatus status = WorkerStatus::Working;
};
// Конкретный сотрудник с кадровыми данными и статусом.
class Worker : public Person
{
    std::string personnelNumber_, position_;
    double rate_;
    bool hasChildren_, isPensioner_, hasDisability_;
    std::vector<std::string> previousJobs_;
    WorkerStatus status_;

  protected:
    // Создаёт сотрудника с указанным статусом для наследников.
    Worker(const WorkerData &data, WorkerStatus status);

  public:
    // Создаёт сотрудника по заполненным кадровым данным.
    explicit Worker(const WorkerData &data);
    // Копирование запрещено, чтобы не дублировать ID.
    Worker(const Worker &) = delete;
    // Присваивание копированием запрещено.
    Worker &operator=(const Worker &) = delete;
    // Перемещение позволяет хранить сотрудников в vector.
    Worker(Worker &&) noexcept = default;
    // Присваивание перемещением не требуется.
    Worker &operator=(Worker &&) = delete;
    // Удаляет сотрудника через базовый класс.
    ~Worker() override = default;
    // Возвращает табельный номер.
    const std::string &getPersonnelNumber() const;
    // Возвращает должность сотрудника.
    const std::string &getPosition() const;
    // Возвращает ставку сотрудника.
    double getRate() const;
    // Сообщает, есть ли у сотрудника дети.
    bool hasChildren() const;
    // Сообщает, является ли сотрудник пенсионером.
    bool isPensioner() const;
    // Сообщает, есть ли у сотрудника инвалидность.
    bool hasDisability() const;
    // Возвращает предыдущие места работы.
    const std::vector<std::string> &getPreviousJobs() const;
    // Возвращает статус в виде enum.
    WorkerStatus getWorkerStatus() const;
    // Возвращает статус текстом.
    virtual std::string getStatus() const;
    // Возвращает все данные сотрудника текстом.
    std::string toString() const override;
    // Сравнивает сотрудников по табельному номеру.
    bool equals(const Worker &other) const;
};
