#include "Department.h"
#include "WorkingWorker.h"
#include "VacationWorker.h"
#include "ChildCareWorker.h"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

enum class MenuItem
{
    Exit = 0,
    ShowAll = 1,
    FindByName = 2,
    FindByPosition = 3,
    FindByRate = 4,
    WithChildren = 5,
    Pensioners = 6,
    WithDisability = 7,
    Vacation = 8,
    ChildCare = 9,
    ShowPositions = 10,
    PreviousJobs = 11
};

void printWorkers(const WorkerList& workers);

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

    department.addWorker(worker1);
    department.addWorker(worker2);
    department.addWorker(worker3);

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

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный ввод\n";
            continue;
        }

        std::cin.ignore(10000, '\n');

        switch (static_cast<MenuItem>(choice))
        {
        case MenuItem::ShowAll:
            printWorkers(department.getAllWorkers());
            break;

        case MenuItem::FindByName:
        {
            std::string name;
            std::cout << "Введите ФИО: ";
            std::getline(std::cin, name);
            printWorkers(department.findWorkersByName(name));
            break;
        }

        case MenuItem::FindByPosition:
        {
            std::string position;
            std::cout << "Введите должность: ";
            std::getline(std::cin, position);
            printWorkers(department.findWorkersByPosition(position));
            break;
        }

        case MenuItem::FindByRate:
        {
            double rate;
            std::cout << "Введите ставку: ";
            if (!(std::cin >> rate))
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Некорректный ввод\n";
                break;
            }

            std::cin.ignore(10000, '\n');
            printWorkers(department.findWorkersByRate(rate));
            break;
        }

        case MenuItem::WithChildren:
            printWorkers(department.findWorkersWithChildren());
            break;

        case MenuItem::Pensioners:
            printWorkers(department.findPensioners());
            break;

        case MenuItem::WithDisability:
            printWorkers(department.findWorkersWithDisability());
            break;

        case MenuItem::Vacation:
            printWorkers(department.findWorkersByStatus("В очередном отпуске"));
            break;

        case MenuItem::ChildCare:
            printWorkers(department.findWorkersByStatus("В отпуске по уходу за ребёнком"));
            break;

        case MenuItem::ShowPositions:
        {
            const std::vector<Position>& positions = department.getPositions();

            for (const Position& position : positions)
            {
                std::cout << position.toString() << "\n";
            }

            break;
        }

        case MenuItem::PreviousJobs:
        {
            std::string number;
            std::cout << "Введите табельный номер: ";
            std::getline(std::cin, number);

            try
            {
                const Worker& worker = department.findWorkerByNumber(number);
                const std::vector<std::string>& jobs = worker.getPreviousJobs();

                for (const std::string& job : jobs)
                {
                    std::cout << job << "\n";
                }
            }
            catch (const std::out_of_range&)
            {
                std::cout << "Работник не найден\n";
            }

            break;
        }

        case MenuItem::Exit:
            std::cout << "Завершение программы\n";
            break;

        default:
            std::cout << "Нет такого пункта меню\n";
            break;
        }
    }

    return 0;
}

void printWorkers(const WorkerList& workers)
{
    if (workers.empty())
    {
        std::cout << "Работники не найдены\n";
        return;
    }

    for (const std::reference_wrapper<const Worker>& worker : workers)
    {
        std::cout << worker.get().toString() << "\n\n";
    }
}
