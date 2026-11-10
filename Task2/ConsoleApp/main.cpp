#include "Department.h"
#include "WorkingWorker.h"
#include "VacationWorker.h"
#include "ChildCareWorker.h"

#include <iostream>
#include <string>
#include <vector>

void printWorkers(const std::vector<const Worker*>& workers);

int main()
{
    Position programmer("Программист", "Разработка программ");
    Position accountant("Бухгалтер", "Работа с финансами");
    Position manager("Менеджер", "Работа с клиентами");

    WorkerData data1;
    data1.fullName = "Иванов Иван Иванович";
    data1.personnelNumber = "001";
    data1.position = "Программист";
    data1.rate = 1.0;
    data1.hasChildren = false;
    data1.isPensioner = false;
    data1.hasDisability = false;
    data1.previousJobs.push_back("ООО Альфа");

    WorkerData data2;
    data2.fullName = "Петров Пётр Петрович";
    data2.personnelNumber = "002";
    data2.position = "Бухгалтер";
    data2.rate = 0.5;
    data2.hasChildren = true;
    data2.isPensioner = true;
    data2.hasDisability = false;
    data2.previousJobs.push_back("ООО Бета");

    WorkerData data3;
    data3.fullName = "Сидорова Анна Сергеевна";
    data3.personnelNumber = "003";
    data3.position = "Менеджер";
    data3.rate = 1.0;
    data3.hasChildren = true;
    data3.isPensioner = false;
    data3.hasDisability = false;
    data3.previousJobs.push_back("ООО Гамма");

    WorkingWorker worker1(data1);
    VacationWorker worker2(data2);
    ChildCareWorker worker3(data3);

    Department department("Отдел кадров");

    department.addPosition(programmer);
    department.addPosition(accountant);
    department.addPosition(manager);

    department.addWorker(&worker1);
    department.addWorker(&worker2);
    department.addWorker(&worker3);

    std::cout << department.toString() << "\n\n";

    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\nМЕНЮ\n";
        std::cout << "1. Показать всех работников\n";
        std::cout << "2. Найти по ФИО\n";
        std::cout << "3. Найти по должности\n";
        std::cout << "4. Найти по ставке\n";
        std::cout << "5. Показать работников с детьми\n";
        std::cout << "6. Показать пенсионеров\n";
        std::cout << "7. Показать работников с инвалидностью\n";
        std::cout << "8. Показать работников в отпуске\n";
        std::cout << "9. Показать работников в отпуске по уходу\n";
        std::cout << "10. Показать должности\n";
        std::cout << "11. Предыдущие места работы\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";

        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        if (choice == 1)
        {
            printWorkers(department.getAllWorkers());
        }
        else if (choice == 2)
        {
            std::string name;
            std::cout << "Введите ФИО: ";
            std::getline(std::cin, name);
            printWorkers(department.findWorkersByName(name));
        }
        else if (choice == 3)
        {
            std::string position;
            std::cout << "Введите должность: ";
            std::getline(std::cin, position);
            printWorkers(department.findWorkersByPosition(position));
        }
        else if (choice == 4)
        {
            double rate;
            std::cout << "Введите ставку: ";
            std::cin >> rate;
            std::cin.ignore(10000, '\n');
            printWorkers(department.findWorkersByRate(rate));
        }
        else if (choice == 5)
        {
            printWorkers(department.findWorkersWithChildren());
        }
        else if (choice == 6)
        {
            printWorkers(department.findPensioners());
        }
        else if (choice == 7)
        {
            printWorkers(department.findWorkersWithDisability());
        }
        else if (choice == 8)
        {
            printWorkers(department.findWorkersByStatus("В очередном отпуске"));
        }
        else if (choice == 9)
        {
            printWorkers(department.findWorkersByStatus("В отпуске по уходу за ребёнком"));
        }
        else if (choice == 10)
        {
            const std::vector<Position>& positions = department.getPositions();

            for (const Position& position : positions)
            {
                std::cout << position.toString() << "\n";
            }
        }
        else if (choice == 11)
        {
            std::string number;
            std::cout << "Введите табельный номер: ";
            std::getline(std::cin, number);

            const Worker* worker = department.findWorkerByNumber(number);

            if (worker == nullptr)
            {
                std::cout << "Работник не найден\n";
            }
            else
            {
                const std::vector<std::string>& jobs = worker->getPreviousJobs();

                for (const std::string& job : jobs)
                {
                    std::cout << job << "\n";
                }
            }
        }
        else if (choice == 0)
        {
            std::cout << "Завершение программы\n";
        }
        else
        {
            std::cout << "Нет такого пункта меню\n";
        }
    }

    return 0;
}

void printWorkers(const std::vector<const Worker*>& workers)
{
    if (workers.empty())
    {
        std::cout << "Работники не найдены\n";
        return;
    }

    for (const Worker* worker : workers)
    {
        std::cout << worker->toString() << "\n\n";
    }
}
