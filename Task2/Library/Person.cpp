#include "Person.h"
#include <stdexcept>

int Person::nextId_ = 1;

Person::Person(const std::string& fullName)
    : id_(nextId_++), fullName_(fullName)
{
    if (fullName_.empty())
    {
        throw std::invalid_argument("ФИО не может быть пустым");
    }
}

int Person::getId() const
{
    return id_;
}

const std::string& Person::getFullName() const
{
    return fullName_;
}
