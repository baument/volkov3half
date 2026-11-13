#pragma once
#include <string>

// Должность с названием и необязательным описанием.
class Position
{
  private:
    std::string name_;
    std::string description_;

  public:
    // Создаёт должность с названием и необязательным описанием.
    Position(const std::string &name, const std::string &description = "");

    // Возвращает название должности.
    const std::string &getName() const;
    // Возвращает описание должности.
    const std::string &getDescription() const;
    // Возвращает должность одной строкой.
    std::string toString() const;
};
