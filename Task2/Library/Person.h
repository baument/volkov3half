#pragma once
#include <string>

/**
 * @brief Базовый класс человека с уникальным идентификатором и ФИО.
 *
 * Класс задаёт общие данные для сотрудников и требует реализации текстового
 * представления в классах-наследниках.
 */
class Person
{
  private:
    static int nextId_;
    int id_;
    std::string fullName_;

  protected:
    /**
     * @brief Создаёт человека с указанным ФИО.
     * @param fullName ФИО человека.
     * @throws std::invalid_argument Если ФИО пустое.
     */
    Person(const std::string &fullName);

  public:
    /**
     * @brief Запрещает копирование человека, чтобы не дублировать ID.
     * @param other Копируемый человек.
     */
    Person(const Person &) = delete;
    /**
     * @brief Запрещает присваивание копированием, чтобы не дублировать ID.
     * @param other Человек для присваивания.
     * @return Эта операция недоступна.
     */
    Person &operator=(const Person &) = delete;
    /**
     * @brief Перемещает данные человека, сохраняя его ID.
     * @param other Перемещаемый человек.
     */
    Person(Person &&other) noexcept;
    /**
     * @brief Запрещает присваивание перемещением.
     * @param other Человек для перемещения.
     * @return Эта операция недоступна.
     */
    Person &operator=(Person &&) = delete;
    /**
     * @brief Виртуально уничтожает человека через базовый класс.
     */
    virtual ~Person() = default;

    /**
     * @brief Возвращает уникальный идентификатор человека.
     * @return Идентификатор человека.
     */
    int getId() const;
    /**
     * @brief Возвращает ФИО человека.
     * @return Константная ссылка на ФИО.
     */
    const std::string &getFullName() const;
    /**
     * @brief Возвращает текстовое описание человека.
     * @return Текстовое описание конкретного наследника.
     */
    virtual std::string toString() const = 0;
};
