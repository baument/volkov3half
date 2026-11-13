#pragma once
#include <string>

// Базовый человек с уникальным идентификатором и ФИО.
class Person
{
  private:
    static int nextId_;
    int id_;
    std::string fullName_;

  protected:
    // Создаёт человека с указанным ФИО.
    Person(const std::string &fullName);

  public:
    // Копирование запрещено, чтобы не дублировать ID.
    Person(const Person &) = delete;
    // Присваивание копированием запрещено по той же причине.
    Person &operator=(const Person &) = delete;
    // Перемещает человека и сохраняет его ID.
    Person(Person &&other) noexcept;
    // Присваивание перемещением не используется.
    Person &operator=(Person &&) = delete;
    // Виртуальный деструктор нужен для наследников.
    virtual ~Person() = default;

    // Возвращает уникальный идентификатор человека.
    int getId() const;
    // Возвращает ФИО человека.
    const std::string &getFullName() const;
    // Возвращает текстовое описание конкретного человека.
    virtual std::string toString() const = 0;
};
