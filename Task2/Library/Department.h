#pragma once
#include "Position.h"
#include "Worker.h"
#include <cstddef>
#include <string>
#include <vector>
/**
 * @brief Хранит индексы сотрудников в хранилище отдела.
 */
using WorkerIndices = std::vector<std::size_t>;
/**
 * @brief Хранит должности и сотрудников отдела кадров по значению.
 */
class Department
{
    /** @brief Название отдела кадров. */
    std::string name_;
    /** @brief Список должностей, доступных в отделе. */
    std::vector<Position> positions_;
    /** @brief Список сотрудников отдела кадров. */
    std::vector<Worker> workers_;

  public:
    /**
     * @brief Создаёт отдел с указанным названием.
     * @param name Название отдела.
     */
    explicit Department(const std::string &name);
    /**
     * @brief Добавляет должность после проверки дубликата по названию.
     * @param position Добавляемая должность.
     * @throws std::invalid_argument Если должность с таким названием уже есть.
     */
    void addPosition(const Position &position);
    /**
     * @brief Создаёт и добавляет сотрудника по его кадровым данным.
     * @param data Кадровые данные добавляемого сотрудника.
     * @throws std::invalid_argument Если табельный номер повторяется, должность
     * отсутствует в отделе или данные сотрудника некорректны.
     */
    void addWorker(const WorkerData &data);
    /**
     * @brief Возвращает сохранённые должности.
     * @return Константная ссылка на список должностей.
     */
    const std::vector<Position> &getPositions() const;
    /**
     * @brief Возвращает сохранённых сотрудников.
     * @return Константная ссылка на список сотрудников.
     */
    const std::vector<Worker> &getWorkers() const;
    /**
     * @brief Возвращает индексы всех сотрудников.
     * @return Список индексов сотрудников.
     */
    std::vector<std::size_t> getAllWorkers() const;
    /**
     * @brief Находит сотрудников по ФИО.
     * @param name ФИО для поиска.
     * @return Индексы найденных сотрудников.
     */
    std::vector<std::size_t> findWorkersByName(const std::string &) const;
    /**
     * @brief Находит сотрудников по должности.
     * @param position Название должности для поиска.
     * @return Индексы найденных сотрудников.
     */
    std::vector<std::size_t> findWorkersByPosition(const std::string &) const;
    /**
     * @brief Находит сотрудников по ставке.
     * @param rate Ставка для поиска.
     * @return Индексы найденных сотрудников.
     */
    std::vector<std::size_t> findWorkersByRate(double) const;
    /**
     * @brief Находит сотрудников с детьми.
     * @return Индексы найденных сотрудников.
     */
    std::vector<std::size_t> findWorkersWithChildren() const;
    /**
     * @brief Находит сотрудников-пенсионеров.
     * @return Индексы найденных сотрудников.
     */
    std::vector<std::size_t> findPensioners() const;
    /**
     * @brief Находит сотрудников с инвалидностью.
     * @return Индексы найденных сотрудников.
     */
    std::vector<std::size_t> findWorkersWithDisability() const;
    /**
     * @brief Находит сотрудников по статусу.
     * @param status Статус для поиска.
     * @return Индексы найденных сотрудников.
     */
    std::vector<std::size_t> findWorkersByStatus(WorkerStatus) const;
    /**
     * @brief Находит сотрудника по табельному номеру.
     * @param personnelNumber Табельный номер для поиска.
     * @return Константная ссылка на найденного сотрудника.
     * @throws std::out_of_range Если сотрудник не найден.
     */
    const Worker &findWorkerByNumber(const std::string &) const;
    /**
     * @brief Возвращает краткую информацию об отделе.
     * @return Название отдела и количество сотрудников.
     */
    std::string toString() const;
};
