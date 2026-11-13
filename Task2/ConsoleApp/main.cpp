#include "Department.h"
#include <iostream>
#include <limits>

/**
 * @brief Перечисляет пункты меню консольного приложения.
 */
enum class MenuItem
{
    Exit = 0,         ///< Завершает работу программы.
    ShowAll = 1,      ///< Выводит всех сотрудников.
    FindByName,       ///< Ищет сотрудников по ФИО.
    FindByPosition,   ///< Ищет сотрудников по должности.
    FindByRate,       ///< Ищет сотрудников по ставке.
    WithChildren,     ///< Выводит сотрудников с детьми.
    Pensioners,       ///< Выводит сотрудников-пенсионеров.
    WithDisability,   ///< Выводит сотрудников с инвалидностью.
    Vacation,         ///< Выводит сотрудников в очередном отпуске.
    ChildCare,        ///< Выводит сотрудников в отпуске по уходу.
    ShowPositions,    ///< Выводит должности отдела.
    PreviousJobs      ///< Выводит предыдущие места работы сотрудника.
};

/**
 * @brief Выводит найденных сотрудников на консоль.
 * @param workers Список сотрудников отдела.
 * @param indices Индексы сотрудников, которые нужно вывести.
 */
void printWorkers(const std::vector<Worker> &workers, const WorkerIndices &indices)
{
    // Выводим сотрудников по индексам, найденным отделом.
    if (indices.empty())
    {
        std::cout << "Работники не найдены\n";
        return;
    }
    for (std::size_t index : indices)
        std::cout << workers.at(index).toString() << "\n\n";
}
/**
 * @brief Запускает консольное приложение отдела кадров.
 * @return Код завершения программы.
 */
int main()
{
    // Создаём отдел, должности и исходные данные сотрудников.
    Department department("Отдел кадров");
    department.addPosition(Position("Программист", "Разработка программ"));
    department.addPosition(Position("Бухгалтер", "Работа с финансами"));
    department.addPosition(Position("Менеджер", "Работа с клиентами"));
    WorkerData first{"Иванов Иван Иванович", "001", "Программист"};
    first.previousJobs.push_back("ООО Альфа");
    WorkerData second{
        "Петров Пётр Петрович", "002", "Бухгалтер", .5, true, true, false, {"ООО Бета"},
        WorkerStatus::Vacation};
    WorkerData third{
        "Сидорова Анна Сергеевна", "003", "Менеджер", 1.0, true, false, false, {"ООО Гамма"},
        WorkerStatus::ChildCare};
    department.addWorker(first);
    department.addWorker(second);
    department.addWorker(third);
    // Обрабатываем команды меню до выбора пункта завершения.
    int choice = -1;
    while (choice != static_cast<int>(MenuItem::Exit))
    {
        std::cout << "\nМЕНЮ\n1. Все\n2. ФИО\n3. Должность\n4. Ставка\n5. Дети\n6. Пенсионеры\n7. "
                     "Инвалидность\n8. Отпуск\n9. Уход\n10. Должности\n11. Предыдущие работы\n0. "
                     "Выход\nВаш выбор: ";
        // Очищаем поток, если пользователь ввёл не число.
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        const std::vector<Worker> &workers = department.getWorkers();
        // Выбираем действие по значению перечисления MenuItem.
        switch (static_cast<MenuItem>(choice))
        {
        case MenuItem::ShowAll:
        {
            WorkerIndices all;
            for (std::size_t i = 0; i < workers.size(); ++i)
                all.push_back(i);
            printWorkers(workers, all);
            break;
        }
        case MenuItem::FindByName:
        {
            std::string value;
            std::getline(std::cin, value);
            printWorkers(workers, department.findWorkersByName(value));
            break;
        }
        case MenuItem::FindByPosition:
        {
            std::string value;
            std::getline(std::cin, value);
            printWorkers(workers, department.findWorkersByPosition(value));
            break;
        }
        case MenuItem::FindByRate:
        {
            double value;
            std::cin >> value;
            printWorkers(workers, department.findWorkersByRate(value));
            break;
        }
        case MenuItem::WithChildren:
            printWorkers(workers, department.findWorkersWithChildren());
            break;
        case MenuItem::Pensioners:
            printWorkers(workers, department.findPensioners());
            break;
        case MenuItem::WithDisability:
            printWorkers(workers, department.findWorkersWithDisability());
            break;
        case MenuItem::Vacation:
            printWorkers(workers, department.findWorkersByStatus(WorkerStatus::Vacation));
            break;
        case MenuItem::ChildCare:
            printWorkers(workers, department.findWorkersByStatus(WorkerStatus::ChildCare));
            break;
        case MenuItem::ShowPositions:
            for (const Position &position : department.getPositions())
                std::cout << position.toString() << '\n';
            break;
        case MenuItem::PreviousJobs:
        {
            std::string number;
            std::getline(std::cin, number);
            try
            {
                for (const std::string &job :
                     department.findWorkerByNumber(number).getPreviousJobs())
                    std::cout << job << '\n';
            }
            catch (const std::out_of_range &)
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
}
