#pragma once
#include "Person.h"
#include <string>
#include <vector>
enum class WorkerStatus
{
    Working,
    Vacation,
    ChildCare
};
struct WorkerData
{
    std::string fullName, personnelNumber, position;
    double rate = 1.0;
    bool hasChildren = false, isPensioner = false, hasDisability = false;
    std::vector<std::string> previousJobs;
    WorkerStatus status = WorkerStatus::Working;
};
class Worker : public Person
{
    std::string personnelNumber_, position_;
    double rate_;
    bool hasChildren_, isPensioner_, hasDisability_;
    std::vector<std::string> previousJobs_;
    WorkerStatus status_;

  protected:
    Worker(const WorkerData &data, WorkerStatus status);

  public:
    explicit Worker(const WorkerData &data);
    Worker(const Worker &) = delete;
    Worker &operator=(const Worker &) = delete;
    Worker(Worker &&) noexcept = default;
    Worker &operator=(Worker &&) = delete;
    ~Worker() override = default;
    const std::string &getPersonnelNumber() const;
    const std::string &getPosition() const;
    double getRate() const;
    bool hasChildren() const;
    bool isPensioner() const;
    bool hasDisability() const;
    const std::vector<std::string> &getPreviousJobs() const;
    WorkerStatus getWorkerStatus() const;
    virtual std::string getStatus() const;
    std::string toString() const override;
    bool equals(const Worker &other) const;
};
