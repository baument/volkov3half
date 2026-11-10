#pragma once

#include "Person.h"
#include <string>
#include <vector>

struct WorkerData
{
    std::string fullName;
    std::string personnelNumber;
    std::string position;
    double rate = 1.0;
    bool hasChildren = false;
    bool isPensioner = false;
    bool hasDisability = false;
    std::vector<std::string> previousJobs;
};

class Worker : public Person
{
private:
    std::string personnelNumber_;
    std::string position_;
    double rate_;
    bool hasChildren_;
    bool isPensioner_;
    bool hasDisability_;
    std::vector<std::string> previousJobs_;

protected:
    Worker(const WorkerData& data);

public:
    ~Worker() override = default;

    const std::string& getPersonnelNumber() const;
    const std::string& getPosition() const;
    double getRate() const;
    bool hasChildren() const;
    bool isPensioner() const;
    bool hasDisability() const;

    const std::vector<std::string>& getPreviousJobs() const;

    virtual std::string getStatus() const = 0;
    std::string toString() const override;
};
