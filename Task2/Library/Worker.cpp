#include "Worker.h"
#include <stdexcept>

Worker::Worker(const WorkerData& data)
    : Person(data.fullName),
      personnelNumber_(data.personnelNumber),
      position_(data.position),
      rate_(data.rate),
      hasChildren_(data.hasChildren),
      isPensioner_(data.isPensioner),
      hasDisability_(data.hasDisability),
      previousJobs_(data.previousJobs)
{
    if (personnelNumber_.empty())
    {
        throw std::invalid_argument("Табельный номер не может быть пустым");
    }

    if (position_.empty())
    {
        throw std::invalid_argument("Должность не может быть пустой");
    }

    if (rate_ <= 0.0)
    {
        throw std::invalid_argument("Ставка должна быть больше нуля");
    }
}

const std::string& Worker::getPersonnelNumber() const
{
    return personnelNumber_;
}

const std::string& Worker::getPosition() const
{
    return position_;
}

double Worker::getRate() const
{
    return rate_;
}

bool Worker::hasChildren() const
{
    return hasChildren_;
}

bool Worker::isPensioner() const
{
    return isPensioner_;
}

bool Worker::hasDisability() const
{
    return hasDisability_;
}

const std::vector<std::string>& Worker::getPreviousJobs() const
{
    return previousJobs_;
}

std::string Worker::toString() const
{
    std::string result;

    result += "ID: " + std::to_string(getId()) + "\n";
    result += "ФИО: " + getFullName() + "\n";
    result += "Табельный номер: " + personnelNumber_ + "\n";
    result += "Должность: " + position_ + "\n";
    result += "Ставка: " + std::to_string(rate_) + "\n";

    if (hasChildren_)
    {
        result += "Есть дети: да\n";
    }
    else
    {
        result += "Есть дети: нет\n";
    }

    if (isPensioner_)
    {
        result += "Пенсионер: да\n";
    }
    else
    {
        result += "Пенсионер: нет\n";
    }

    if (hasDisability_)
    {
        result += "Инвалидность: да\n";
    }
    else
    {
        result += "Инвалидность: нет\n";
    }

    result += "Статус: " + getStatus();

    return result;
}
