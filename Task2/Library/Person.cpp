#include "Person.h"
#include <stdexcept>
#include <utility>

int Person::nextId_ = 1;

Person::Person(const std::string &fullName) : id_(nextId_++), fullName_(fullName)
{
    if (fullName_.empty())
    {
        throw std::invalid_argument("ФИО не может быть пустым");
    }
}

Person::Person(Person &&other) noexcept : id_(other.id_), fullName_(std::move(other.fullName_))
{
    other.id_ = 0;
}

int Person::getId() const { return id_; }

const std::string &Person::getFullName() const { return fullName_; }
