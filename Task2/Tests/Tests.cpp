#include "Department.h"
#include "WorkingWorker.h"
#include "VacationWorker.h"
#include "ChildCareWorker.h"

#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

void assertInvalidArgument(const std::function<void()>& action)
{
    bool wasThrown = false;

    try
    {
        action();
    }
    catch (const std::invalid_argument&)
    {
        wasThrown = true;
    }

    assert(wasThrown);
}

void assertOutOfRange(const std::function<void()>& action)
{
    bool wasThrown = false;

    try
    {
        action();
    }
    catch (const std::out_of_range&)
    {
        wasThrown = true;
    }

    assert(wasThrown);
}

WorkerData makeWorkerData(
    const std::string& fullName,
    const std::string& personnelNumber,
    const std::string& position)
{
    WorkerData data;
    data.fullName = fullName;
    data.personnelNumber = personnelNumber;
    data.position = position;
    return data;
}

void testPosition()
{
    Position programmer("Программист", "Разработка программ");
    Position accountant("Бухгалтер");

    assert(programmer.getName() == "Программист");
    assert(programmer.getDescription() == "Разработка программ");
    assert(programmer.toString() == "Программист — Разработка программ");
    assert(accountant.getName() == "Бухгалтер");
    assert(accountant.getDescription() == "");
    assert(accountant.toString() == "Бухгалтер");

    assertInvalidArgument([] { Position invalidPosition(""); });
}

void testWorkerAndDerivedClasses()
{
    WorkerData workingData = makeWorkerData("Иванов Иван", "001", "Программист");
    workingData.hasChildren = true;
    workingData.previousJobs = {"ООО Альфа", "ООО Бета"};

    WorkerData vacationData = makeWorkerData("Петров Пётр", "002", "Бухгалтер");
    vacationData.rate = 0.5;
    vacationData.isPensioner = true;

    WorkerData childCareData = makeWorkerData("Сидорова Анна", "003", "Менеджер");
    childCareData.hasDisability = true;

    WorkingWorker workingWorker(workingData);
    VacationWorker vacationWorker(vacationData);
    ChildCareWorker childCareWorker(childCareData);

    const Person& person = workingWorker;
    const Worker& polymorphicWorker = vacationWorker;

    assert(workingWorker.getFullName() == "Иванов Иван");
    assert(workingWorker.getPersonnelNumber() == "001");
    assert(workingWorker.getPosition() == "Программист");
    assert(workingWorker.getRate() == 1.0);
    assert(workingWorker.hasChildren());
    assert(!workingWorker.isPensioner());
    assert(!workingWorker.hasDisability());
    assert(workingWorker.getPreviousJobs().size() == 2);
    assert(workingWorker.getPreviousJobs().at(0) == "ООО Альфа");
    assert(workingWorker.getPreviousJobs().at(1) == "ООО Бета");
    assert(workingWorker.getStatus() == "Работает");
    assert(vacationWorker.getStatus() == "В очередном отпуске");
    assert(childCareWorker.getStatus() == "В отпуске по уходу за ребёнком");
    assert(workingWorker.getId() != vacationWorker.getId());
    assert(vacationWorker.getId() != childCareWorker.getId());
    assert(polymorphicWorker.getStatus() == "В очередном отпуске");

    const std::string expectedWorkingText =
        "ID: " + std::to_string(workingWorker.getId()) + "\n" +
        "ФИО: Иванов Иван\n" +
        "Табельный номер: 001\n" +
        "Должность: Программист\n" +
        "Ставка: 1.000000\n" +
        "Есть дети: да\n" +
        "Пенсионер: нет\n" +
        "Инвалидность: нет\n" +
        "Статус: Работает";

    assert(workingWorker.toString() == expectedWorkingText);
    assert(person.toString() == expectedWorkingText);

    WorkerData invalidName = makeWorkerData("", "004", "Программист");
    WorkerData invalidNumber = makeWorkerData("Тест Тест", "", "Программист");
    WorkerData invalidPosition = makeWorkerData("Тест Тест", "005", "");
    WorkerData invalidRate = makeWorkerData("Тест Тест", "006", "Программист");
    invalidRate.rate = 0.0;

    assertInvalidArgument([&invalidName] { WorkingWorker worker(invalidName); });
    assertInvalidArgument([&invalidNumber] { WorkingWorker worker(invalidNumber); });
    assertInvalidArgument([&invalidPosition] { WorkingWorker worker(invalidPosition); });
    assertInvalidArgument([&invalidRate] { WorkingWorker worker(invalidRate); });
}

void testDepartment()
{
    Position programmer("Программист", "Разработка программ");
    Position accountant("Бухгалтер", "Работа с финансами");
    Position manager("Менеджер", "Работа с клиентами");

    WorkerData data1 = makeWorkerData("Иванов Иван", "101", "Программист");
    data1.hasChildren = true;
    data1.previousJobs = {"ООО Альфа"};

    WorkerData data2 = makeWorkerData("Петров Пётр", "102", "Бухгалтер");
    data2.rate = 0.5;
    data2.isPensioner = true;

    WorkerData data3 = makeWorkerData("Сидорова Анна", "103", "Менеджер");
    data3.hasDisability = true;

    WorkerData duplicateNumberData = makeWorkerData("Смирнов Сергей", "101", "Программист");
    WorkerData missingPositionData = makeWorkerData("Кузнецов Олег", "104", "Юрист");

    WorkingWorker worker1(data1);
    VacationWorker worker2(data2);
    ChildCareWorker worker3(data3);
    WorkingWorker duplicateNumberWorker(duplicateNumberData);
    WorkingWorker missingPositionWorker(missingPositionData);

    Department department("Отдел кадров");

    department.addPosition(programmer);
    department.addPosition(accountant);
    department.addPosition(manager);

    assert(department.getPositions().size() == 3);
    assert(department.getPositions().at(0).getName() == "Программист");
    assert(department.getPositions().at(1).getDescription() == "Работа с финансами");
    assert(department.toString() == "Отдел кадров. Количество работников: 0");

    assertInvalidArgument([&department, &programmer] { department.addPosition(programmer); });
    assertInvalidArgument([&department, &missingPositionWorker] { department.addWorker(missingPositionWorker); });

    department.addWorker(worker1);
    department.addWorker(worker2);
    department.addWorker(worker3);

    assert(department.getWorkers().size() == 3);
    assert(department.getAllWorkers().size() == 3);
    assert(department.getWorkers().at(0).get().getId() == worker1.getId());
    assert(department.getAllWorkers().at(1).get().getPersonnelNumber() == "102");
    assert(department.toString() == "Отдел кадров. Количество работников: 3");

    assert(department.findWorkersByName("Иванов Иван").size() == 1);
    assert(department.findWorkersByName("Иванов Иван").at(0).get().getId() == worker1.getId());
    assert(department.findWorkersByName("Нет такого").empty());
    assert(department.findWorkersByPosition("Программист").size() == 1);
    assert(department.findWorkersByPosition("Нет такой").empty());
    assert(department.findWorkersByRate(0.5).size() == 1);
    assert(department.findWorkersByRate(2.0).empty());
    assert(department.findWorkersWithChildren().size() == 1);
    assert(department.findPensioners().size() == 1);
    assert(department.findWorkersWithDisability().size() == 1);
    assert(department.findWorkersByStatus("Работает").size() == 1);
    assert(department.findWorkersByStatus("В очередном отпуске").size() == 1);
    assert(department.findWorkersByStatus("В отпуске по уходу за ребёнком").size() == 1);
    assert(department.findWorkersByStatus("Неизвестный статус").empty());

    const Worker& foundWorker = department.findWorkerByNumber("102");
    assert(foundWorker.getId() == worker2.getId());
    assert(foundWorker.getPreviousJobs().empty());
    assertOutOfRange([&department] { department.findWorkerByNumber("999"); });

    assertInvalidArgument([&department, &worker1] { department.addWorker(worker1); });
    assertInvalidArgument([&department, &duplicateNumberWorker] { department.addWorker(duplicateNumberWorker); });
}

int main()
{
    testPosition();
    testWorkerAndDerivedClasses();
    testDepartment();

    std::cout << "Все тесты пройдены\n";

    return 0;
}
