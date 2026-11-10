#include "Department.h"
#include "WorkingWorker.h"
#include "VacationWorker.h"
#include "ChildCareWorker.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

int main()
{
    Position programmer("Программист");
    Position accountant("Бухгалтер");

    WorkerData data1;
    data1.fullName = "Иванов Иван";
    data1.personnelNumber = "001";
    data1.position = "Программист";
    data1.rate = 1.0;
    data1.hasChildren = false;
    data1.isPensioner = false;

    WorkerData data2;
    data2.fullName = "Петров Пётр";
    data2.personnelNumber = "002";
    data2.position = "Бухгалтер";
    data2.rate = 0.5;
    data2.hasChildren = true;
    data2.isPensioner = true;

    WorkerData data3;
    data3.fullName = "Сидорова Анна";
    data3.personnelNumber = "003";
    data3.position = "Программист";
    data3.rate = 1.0;

    WorkingWorker worker1(data1);
    VacationWorker worker2(data2);
    ChildCareWorker worker3(data3);

    Department department("Отдел кадров");

    department.addPosition(programmer);
    department.addPosition(accountant);

    department.addWorker(&worker1);
    department.addWorker(&worker2);
    department.addWorker(&worker3);

    assert(department.getWorkers().size() == 3);
    assert(department.getAllWorkers().size() == 3);

    assert(department.findWorkersByName("Иванов Иван").size() == 1);
    assert(department.findWorkersByPosition("Программист").size() == 2);
    assert(department.findWorkersByRate(0.5).size() == 1);

    assert(department.findWorkersWithChildren().size() == 1);
    assert(department.findPensioners().size() == 1);

    assert(department.findWorkersByStatus("В очередном отпуске").size() == 1);
    assert(department.findWorkersByStatus("В отпуске по уходу за ребёнком").size() == 1);

    assert(department.findWorkerByNumber("002") == &worker2);
    assert(department.findWorkerByNumber("999") == nullptr);

    bool duplicateWasRejected = false;

    try
    {
        department.addWorker(&worker1);
    }
    catch (const std::invalid_argument&)
    {
        duplicateWasRejected = true;
    }

    assert(duplicateWasRejected);

    bool nullWasRejected = false;

    try
    {
        department.addWorker(nullptr);
    }
    catch (const std::invalid_argument&)
    {
        nullWasRejected = true;
    }

    assert(nullWasRejected);

    std::cout << "Все тесты пройдены\n";

    return 0;
}
