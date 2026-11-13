#pragma once
#include "Person.h"
#include <string>
#include <vector>
/**
 * @brief Перечисляет возможные статусы сотрудника.
 */
enum class WorkerStatus
{
    Working,   ///< Сотрудник работает.
    Vacation,  ///< Сотрудник находится в очередном отпуске.
    ChildCare  ///< Сотрудник находится в отпуске по уходу за ребёнком.
};
/**
 * @brief Содержит данные, необходимые для создания сотрудника.
 */
struct WorkerData
{
    /** @brief ФИО сотрудника; значение не должно быть пустым. */
    std::string fullName;
    /** @brief Табельный номер сотрудника; значение не должно быть пустым. */
    std::string personnelNumber;
    /** @brief Название должности сотрудника; значение не должно быть пустым. */
    std::string position;
    /** @brief Ставка сотрудника; должна быть положительным конечным числом. */
    double rate = 1.0;
    /** @brief Признак наличия детей у сотрудника. */
    bool hasChildren = false;
    /** @brief Признак пенсионного статуса сотрудника. */
    bool isPensioner = false;
    /** @brief Признак наличия инвалидности у сотрудника. */
    bool hasDisability = false;
    /** @brief Список предыдущих мест работы сотрудника. */
    std::vector<std::string> previousJobs;
    /** @brief Текущий статус сотрудника. */
    WorkerStatus status = WorkerStatus::Working;
};
/**
 * @brief Хранит кадровые данные конкретного сотрудника и его статус.
 *
 * Наследует уникальный ID и ФИО от Person. Метод getStatus() является
 * виртуальным и может быть переопределён специализированными наследниками.
 */
class Worker : public Person
{
    /** @brief Табельный номер сотрудника. */
    std::string personnelNumber_;
    /** @brief Название должности сотрудника. */
    std::string position_;
    /** @brief Ставка сотрудника. */
    double rate_;
    /** @brief Признак наличия детей у сотрудника. */
    bool hasChildren_;
    /** @brief Признак пенсионного статуса сотрудника. */
    bool isPensioner_;
    /** @brief Признак наличия инвалидности у сотрудника. */
    bool hasDisability_;
    /** @brief Список предыдущих мест работы сотрудника. */
    std::vector<std::string> previousJobs_;
    /** @brief Текущий статус сотрудника. */
    WorkerStatus status_;

  protected:
    /**
     * @brief Создаёт сотрудника с указанным статусом для классов-наследников.
     * @param data Кадровые данные сотрудника.
     * @param status Статус сотрудника.
     * @throws std::invalid_argument Если данные сотрудника некорректны.
     */
    Worker(const WorkerData &data, WorkerStatus status);

  public:
    /**
     * @brief Создаёт сотрудника по заполненным кадровым данным.
     * @param data Кадровые данные сотрудника.
     * @throws std::invalid_argument Если ФИО, табельный номер или должность пусты,
     * либо ставка не является положительным конечным числом.
     */
    explicit Worker(const WorkerData &data);
    /**
     * @brief Запрещает копирование сотрудника, чтобы не дублировать ID.
     * @param other Копируемый сотрудник.
     */
    Worker(const Worker &) = delete;
    /**
     * @brief Запрещает присваивание копированием сотрудника.
     * @param other Сотрудник для присваивания.
     * @return Эта операция недоступна.
     */
    Worker &operator=(const Worker &) = delete;
    /**
     * @brief Перемещает сотрудника при изменении размера vector.
     * @param other Перемещаемый сотрудник.
     */
    Worker(Worker &&) noexcept = default;
    /**
     * @brief Запрещает присваивание перемещением сотрудника.
     * @param other Сотрудник для перемещения.
     * @return Эта операция недоступна.
     */
    Worker &operator=(Worker &&) = delete;
    /**
     * @brief Уничтожает сотрудника через базовый класс.
     */
    ~Worker() override = default;
    /**
     * @brief Возвращает табельный номер сотрудника.
     * @return Константная ссылка на табельный номер.
     */
    const std::string &getPersonnelNumber() const;
    /**
     * @brief Возвращает должность сотрудника.
     * @return Константная ссылка на должность.
     */
    const std::string &getPosition() const;
    /**
     * @brief Возвращает ставку сотрудника.
     * @return Значение ставки.
     */
    double getRate() const;
    /**
     * @brief Сообщает, есть ли у сотрудника дети.
     * @return true, если у сотрудника есть дети, иначе false.
     */
    bool hasChildren() const;
    /**
     * @brief Сообщает, является ли сотрудник пенсионером.
     * @return true, если сотрудник пенсионер, иначе false.
     */
    bool isPensioner() const;
    /**
     * @brief Сообщает, есть ли у сотрудника инвалидность.
     * @return true, если у сотрудника есть инвалидность, иначе false.
     */
    bool hasDisability() const;
    /**
     * @brief Возвращает предыдущие места работы сотрудника.
     * @return Константная ссылка на список предыдущих мест работы.
     */
    const std::vector<std::string> &getPreviousJobs() const;
    /**
     * @brief Возвращает статус сотрудника в виде перечисления.
     * @return Значение WorkerStatus.
     */
    WorkerStatus getWorkerStatus() const;
    /**
     * @brief Возвращает статус сотрудника текстом.
     * @return Строковое представление статуса.
     * @throws std::logic_error Если статус не соответствует значению WorkerStatus.
     */
    virtual std::string getStatus() const;
    /**
     * @brief Возвращает все данные сотрудника текстом.
     * @return Многострочное описание сотрудника.
     */
    std::string toString() const override;
    /**
     * @brief Сравнивает сотрудников по табельному номеру.
     * @param other Сотрудник для сравнения.
     * @return true, если табельные номера совпадают, иначе false.
     */
    bool equals(const Worker &other) const;
};
