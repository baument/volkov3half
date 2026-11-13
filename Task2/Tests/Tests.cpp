#include "ChildCareWorker.h"
#include "Department.h"
#include "VacationWorker.h"
#include "WorkingWorker.h"

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace
{
/** @brief Считает количество выполненных тестовых проверок. */
int checks = 0;

/**
 * @brief Проверяет условие и прекращает тестирование при ошибке.
 * @param condition Проверяемое условие.
 * @param message Сообщение об ошибке проверки.
 * @throws std::runtime_error Если условие ложно.
 */
void check(bool condition, const std::string &message)
{
    ++checks;
    if (!condition)
    {
        throw std::runtime_error(message);
    }
}

/**
 * @brief Проверяет выброс исключения std::invalid_argument.
 * @param action Действие, которое должно выбросить исключение.
 * @throws std::runtime_error Если ожидаемое исключение не выброшено.
 */
void checkInvalidArgument(const std::function<void()> &action)
{
    // Проверяем, что действие отклоняет неверные данные.
    bool thrown = false;
    try
    {
        action();
    }
    catch (const std::invalid_argument &)
    {
        thrown = true;
    }
    check(thrown, "Ожидалось std::invalid_argument");
}

/**
 * @brief Проверяет выброс исключения std::out_of_range.
 * @param action Действие, которое должно выбросить исключение.
 * @throws std::runtime_error Если ожидаемое исключение не выброшено.
 */
void checkOutOfRange(const std::function<void()> &action)
{
    // Проверяем поиск отсутствующего значения.
    bool thrown = false;
    try
    {
        action();
    }
    catch (const std::out_of_range &)
    {
        thrown = true;
    }
    check(thrown, "Ожидалось std::out_of_range");
}

/**
 * @brief Создаёт минимальный набор данных сотрудника для теста.
 * @param name ФИО сотрудника.
 * @param number Табельный номер сотрудника.
 * @param position Название должности сотрудника.
 * @return Заполненная структура WorkerData.
 */
WorkerData makeData(const std::string &name, const std::string &number, const std::string &position)
{
    // Создаём минимальный набор данных для теста.
    WorkerData data;
    data.fullName = name;
    data.personnelNumber = number;
    data.position = position;
    return data;
}

/**
 * @brief Проверяет Person через конкретного наследника.
 *
 * Проверяет ФИО, уникальный ID, виртуальный toString() и отказ от пустого ФИО.
 */
void testPerson()
{
    WorkerData firstData = makeData("Иванов Иван", "P-1", "Программист");
    WorkerData secondData = makeData("Петров Пётр", "P-2", "Программист");
    WorkingWorker first(firstData);
    WorkingWorker second(secondData);
    const Person &person = first;

    check(person.getFullName() == "Иванов Иван", "Person::getFullName");
    check(person.getId() > 0, "Person::getId положителен");
    check(person.getId() != second.getId(), "ID уникальны");
    check(person.toString().find("Иванов Иван") != std::string::npos,
          "Виртуальный Person::toString");

    WorkerData invalid = makeData("", "P-3", "Программист");
    checkInvalidArgument([&invalid] { WorkingWorker worker(invalid); });
}

/**
 * @brief Проверяет Position и обработку пустого названия.
 */
void testPosition()
{
    Position programmer("Программист", "Разработка");
    Position trainee("Стажёр");

    check(programmer.getName() == "Программист", "Position::getName");
    check(programmer.getDescription() == "Разработка", "Position::getDescription");
    check(programmer.toString() == "Программист — Разработка", "Position::toString с описанием");
    check(trainee.getDescription().empty(), "Описание по умолчанию");
    check(trainee.toString() == "Стажёр", "Position::toString без описания");
    checkInvalidArgument([] { Position position(""); });
}

/**
 * @brief Проверяет Worker, его данные, перемещение и сравнение.
 */
void testWorker()
{
    WorkerData data = makeData("Сидоров Сергей", "W-1", "Программист");
    data.rate = 0.75;
    data.hasChildren = true;
    data.isPensioner = true;
    data.hasDisability = true;
    data.previousJobs = {"Альфа", "Бета"};
    data.status = WorkerStatus::Working;
    Worker worker(data);

    check(worker.getPersonnelNumber() == "W-1", "Worker::getPersonnelNumber");
    check(worker.getPosition() == "Программист", "Worker::getPosition");
    check(std::abs(worker.getRate() - 0.75) < 1e-9, "Worker::getRate");
    check(worker.hasChildren(), "Worker::hasChildren");
    check(worker.isPensioner(), "Worker::isPensioner");
    check(worker.hasDisability(), "Worker::hasDisability");
    check(worker.getPreviousJobs().size() == 2 && worker.getPreviousJobs().at(1) == "Бета",
          "Worker::getPreviousJobs");
    check(worker.getWorkerStatus() == WorkerStatus::Working, "Worker::getWorkerStatus");
    check(worker.getStatus() == "Работает", "Worker::getStatus");
    check(worker.toString().find("Табельный номер: W-1") != std::string::npos, "Worker::toString");
    check(worker.equals(worker), "Worker::equals для того же работника");

    WorkerData sameNumber = makeData("Другой", "W-1", "Программист");
    WorkerData otherNumber = makeData("Другой", "W-2", "Программист");
    Worker same(sameNumber);
    Worker other(otherNumber);
    check(worker.equals(same), "Worker::equals для одинакового номера");
    check(!worker.equals(other), "Worker::equals для разных номеров");

    WorkerData movableData = makeData("Перемещаемый", "W-5", "Программист");
    Worker movable(movableData);
    const int movableId = movable.getId();
    Worker moved(std::move(movable));
    check(moved.getId() == movableId && moved.getPersonnelNumber() == "W-5",
          "Перемещение Worker сохраняет ID и данные");

    WorkerData emptyNumber = makeData("Тест", "", "Программист");
    WorkerData emptyPosition = makeData("Тест", "W-3", "");
    WorkerData invalidRate = makeData("Тест", "W-4", "Программист");
    invalidRate.rate = std::numeric_limits<double>::quiet_NaN();
    checkInvalidArgument([&emptyNumber] { Worker worker(emptyNumber); });
    checkInvalidArgument([&emptyPosition] { Worker worker(emptyPosition); });
    checkInvalidArgument([&invalidRate] { Worker worker(invalidRate); });
}

/**
 * @brief Проверяет WorkingWorker и виртуальный вызов статуса.
 */
void testWorkingWorker()
{
    WorkingWorker worker(makeData("Работающий", "WW-1", "Программист"));
    const Worker &polymorphic = worker;
    check(worker.getStatus() == "Работает", "WorkingWorker::getStatus");
    check(polymorphic.getStatus() == "Работает", "Полиморфизм WorkingWorker");
}

/**
 * @brief Проверяет VacationWorker и его статус отпуска.
 */
void testVacationWorker()
{
    VacationWorker worker(makeData("Отпуск", "VW-1", "Программист"));
    const Person &polymorphic = worker;
    check(worker.getStatus() == "В очередном отпуске", "VacationWorker::getStatus");
    check(polymorphic.toString().find("В очередном отпуске") != std::string::npos,
          "Полиморфизм VacationWorker");
}

/**
 * @brief Проверяет ChildCareWorker и его статус отпуска по уходу.
 */
void testChildCareWorker()
{
    ChildCareWorker worker(makeData("Уход", "CW-1", "Программист"));
    const Worker &polymorphic = worker;
    check(worker.getStatus() == "В отпуске по уходу за ребёнком", "ChildCareWorker::getStatus");
    check(polymorphic.getStatus().find("уходу") != std::string::npos,
          "Полиморфизм ChildCareWorker");
}

/**
 * @brief Проверяет все публичные операции Department и пограничные случаи поиска.
 */
void testDepartment()
{
    Department department("Отдел кадров");
    Position programmer("Программист", "Разработка");
    Position accountant("Бухгалтер");
    department.addPosition(programmer);
    department.addPosition(accountant);

    WorkerData first = makeData("Иванов Иван", "001", "Программист");
    first.hasChildren = true;
    first.previousJobs = {"Альфа"};
    WorkerData second = makeData("Петров Пётр", "002", "Бухгалтер");
    second.rate = 0.5;
    second.isPensioner = true;
    second.status = WorkerStatus::Vacation;
    WorkerData third = makeData("Сидорова Анна", "003", "Программист");
    third.hasDisability = true;
    third.status = WorkerStatus::ChildCare;

    department.addWorker(first);
    department.addWorker(second);
    department.addWorker(third);

    check(department.getPositions().size() == 2, "Department::getPositions");
    check(department.getPositions().at(0).getName() == "Программист", "Должность сохранена");
    check(department.getWorkers().size() == 3, "Department::getWorkers");
    check(department.getAllWorkers() == WorkerIndices({0, 1, 2}), "Department::getAllWorkers");
    check(department.findWorkersByName("Иванов Иван") == WorkerIndices({0}),
          "Department::findWorkersByName");
    check(department.findWorkersByName("Нет").empty(), "Поиск по отсутствующему имени");
    check(department.findWorkersByPosition("Программист") == WorkerIndices({0, 2}),
          "Department::findWorkersByPosition");
    check(department.findWorkersByPosition("Юрист").empty(), "Поиск по отсутствующей должности");
    check(department.findWorkersByRate(0.5) == WorkerIndices({1}), "Department::findWorkersByRate");
    check(department.findWorkersByRate(2.0).empty(), "Поиск по отсутствующей ставке");
    check(department.findWorkersWithChildren() == WorkerIndices({0}),
          "Department::findWorkersWithChildren");
    check(department.findPensioners() == WorkerIndices({1}), "Department::findPensioners");
    check(department.findWorkersWithDisability() == WorkerIndices({2}),
          "Department::findWorkersWithDisability");
    check(department.findWorkersByStatus(WorkerStatus::Working) == WorkerIndices({0}),
          "Department::findWorkersByStatus Working");
    check(department.findWorkersByStatus(WorkerStatus::Vacation) == WorkerIndices({1}),
          "Department::findWorkersByStatus Vacation");
    check(department.findWorkersByStatus(WorkerStatus::ChildCare) == WorkerIndices({2}),
          "Department::findWorkersByStatus ChildCare");
    check(department.findWorkerByNumber("002").getFullName() == "Петров Пётр",
          "Department::findWorkerByNumber");
    check(department.toString() == "Отдел кадров. Количество работников: 3",
          "Department::toString");

    checkInvalidArgument([&department, &programmer] { department.addPosition(programmer); });
    checkInvalidArgument([&department, &first] { department.addWorker(first); });
    WorkerData unknownPosition = makeData("Новый", "004", "Юрист");
    checkInvalidArgument([&department, &unknownPosition]
                         { department.addWorker(unknownPosition); });
    checkOutOfRange([&department] { department.findWorkerByNumber("999"); });
}
} // namespace

/**
 * @brief Запускает все автоматические тесты проекта.
 * @return Код завершения тестового приложения.
 */
int main()
{
    testPerson();
    testPosition();
    testWorker();
    testWorkingWorker();
    testVacationWorker();
    testChildCareWorker();
    testDepartment();

    std::cout << "Все проверки пройдены: " << checks << '\n';
    return 0;
}
