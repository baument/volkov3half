#include "Position.h"
#include <stdexcept>

Position::Position(const std::string &name, const std::string &description)
    : name_(name), description_(description)
{
    // Отклоняем должность без названия.
    if (name_.empty())
    {
        throw std::invalid_argument("Название должности не может быть пустым");
    }
}

const std::string &Position::getName() const { return name_; }

const std::string &Position::getDescription() const { return description_; }

std::string Position::toString() const
{
    if (description_.empty())
    {
        return name_;
    }
    return name_ + " — " + description_;
}
