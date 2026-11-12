#pragma once
#include <string>

class Person
{
private:
    static int nextId_;
    int id_;
    std::string fullName_;

protected:
    Person(const std::string& fullName);

public:
    Person(const Person&) = delete;
    Person& operator=(const Person&) = delete;
    Person(Person&& other) noexcept;
    Person& operator=(Person&&) = delete;
    virtual ~Person() = default;

    int getId() const;
    const std::string& getFullName() const;
    virtual std::string toString() const = 0;
};
