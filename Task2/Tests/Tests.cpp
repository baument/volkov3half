#include "ChildCareWorker.h"
#include "Department.h"
#include "VacationWorker.h"
#include "WorkingWorker.h"
#include <cassert>
#include <iostream>
#include <limits>
#include <stdexcept>

int main()
{
    Position programmer("Программист"), accountant("Бухгалтер");
    WorkerData a{"Иванов Иван", "001", "Программист"};
    a.previousJobs = {"Альфа"};
    WorkerData b{"Петров Пётр", "002", "Бухгалтер",           .5, true, true,
                 false,         {},    WorkerStatus::Vacation};
    WorkerData c{"Сидорова Анна",        "003", "Программист", 1.0, true, false, true, {},
                 WorkerStatus::ChildCare};
    WorkingWorker working(a);
    VacationWorker vacation(b);
    ChildCareWorker child(c);
    const Person &person = vacation;
    assert(person.toString().find("отпуске") != std::string::npos);
    assert(working.getStatus() == "Работает" &&
           child.getStatus().find("уходу") != std::string::npos);
    Department d("Отдел кадров");
    d.addPosition(programmer);
    d.addPosition(accountant);
    d.addWorker(a);
    d.addWorker(b);
    d.addWorker(c);
    assert(d.getWorkers().size() == 3 && d.getAllWorkers().size() == 3 &&
           d.findWorkersByName("Иванов Иван").size() == 1 &&
           d.findWorkersByPosition("Программист").size() == 2 &&
           d.findWorkersByRate(.5).size() == 1 && d.findWorkersWithChildren().size() == 2 &&
           d.findPensioners().size() == 1 && d.findWorkersWithDisability().size() == 1 &&
           d.findWorkersByStatus(WorkerStatus::Vacation).size() == 1);
    assert(d.findWorkerByNumber("001").equals(d.getWorkers().at(0)) &&
           d.findWorkerByNumber("001").getPreviousJobs().at(0) == "Альфа");
    int id = d.getWorkers().at(0).getId();
    for (int i = 4; i <= 30; ++i)
    {
        WorkerData x = a;
        x.fullName = "Новый " + std::to_string(i);
        x.personnelNumber = "N" + std::to_string(i);
        d.addWorker(x);
    }
    assert(d.getWorkers().at(0).getId() == id);
    bool duplicate = false;
    try
    {
        d.addWorker(a);
    }
    catch (const std::invalid_argument &)
    {
        duplicate = true;
    }
    assert(duplicate);
    bool badRate = false;
    try
    {
        WorkerData x = a;
        x.personnelNumber = "bad";
        x.rate = std::numeric_limits<double>::quiet_NaN();
        d.addWorker(x);
    }
    catch (const std::invalid_argument &)
    {
        badRate = true;
    }
    assert(badRate);
    bool missing = false;
    try
    {
        d.findWorkerByNumber("none");
    }
    catch (const std::out_of_range &)
    {
        missing = true;
    }
    assert(missing);
    std::cout << "Все проверки пройдены\n";
}
