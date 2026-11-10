#pragma once
#include <string>

class Position
{
private:
    std::string name_;
    std::string description_;

public:
    Position(const std::string& name, const std::string& description = "");

    const std::string& getName() const;
    const std::string& getDescription() const;
    std::string toString() const;
};
