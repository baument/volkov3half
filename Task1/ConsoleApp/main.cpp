#include "ConstantGenerator.h"
#include "Generator.h"
#include "IStreamGenerator.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"
#include "ZeroGenerator.h"

#include <cstddef>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>

using namespace miit::algebra;

namespace
{
    /**
     * @brief Очистить std::cin после некорректного ввода.
     */
    void clearInput()
    {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }


    /**
     * @brief Безопасно прочитать любое значение int.
     *
     * Если пользователь вместо числа введёт текст, программа не падает:
     * выводится сообщение об ошибке и ввод повторяется.
     */
    int readInt(const std::string& prompt)
    {
        while (true)
        {
            std::cout << prompt;

            int value = 0;

            if (std::cin >> value)
            {
                return value;
            }
            else
            {
                std::cout
                    << "ERROR: expected an integer. Please try again.\n";

                clearInput();
            }
        }
    }


    /**
     * @brief Безопасно прочитать положительный размер матрицы.
     *
     * Сначала читаем long long, а не size_t. Это важно: если сразу читать
     * отрицательное число в беззнаковый size_t, оно может превратиться
     * в очень большое положительное значение.
     */
    std::size_t readPositiveSize(const std::string& prompt)
    {
        while (true)
        {
            std::cout << prompt;

            long long value = 0;

            if (std::cin >> value)
            {
                if (value > 0)
                {
                    return static_cast<std::size_t>(value);
                }
                else
                {
                    std::cout
                        << "ERROR: matrix size must be greater than zero.\n";
                }
            }
            else
            {
                std::cout
                    << "ERROR: expected a whole positive number.\n";

                clearInput();
            }
        }
    }


    /**
     * @brief Прочитать пункт меню в заданном диапазоне.
     */
    int readMenuChoice(
        const std::string& prompt,
        int minChoice,
        int maxChoice
    )
    {
        while (true)
        {
            const int choice = readInt(prompt);

            if (choice >= minChoice && choice <= maxChoice)
            {
                return choice;
            }
            else
            {
                std::cout
                    << "ERROR: choose a number from "
                    << minChoice
                    << " to "
                    << maxChoice
                    << ".\n";
            }
        }
    }


    /**
     * @brief Показать обе задачи варианта на одной исходной матрице.
     */
    void runTasks(
        std::size_t rows,
        std::size_t columns,
        Generator& generator
    )
    {
        // Task1 создаёт и заполняет исходную матрицу через Generator.
        Task1 task1(rows, columns, generator);

        // Сохраняем исходную матрицу до изменения Task1.
        const Matrix<int> original = task1.getMatrix();

        // Task2 получает отдельную копию той же исходной матрицы.
        // Поэтому Task1 и Task2 демонстрируются независимо друг от друга.
        Task2 task2(original, generator);

        std::cout << "\n--- ORIGINAL MATRIX ---\n";
        std::cout << original.toString();

        task1.solve();

        std::cout << "\n--- TASK 1 RESULT ---\n";
        std::cout
            << "Maximum value(s) in each row changed sign:\n";
        std::cout << task1.getMatrix().toString();

        task2.solve();

        std::cout << "\n--- TASK 2 RESULT ---\n";
        std::cout
            << "A zero column was inserted after every column "
            << "containing the global maximum:\n";
        std::cout << task2.getMatrix().toString();

        // Дополнительно показываем требуемые перегруженные операторы.
        Matrix<int> shifted = original;
        shifted << 1;

        std::cout << "\n--- OPERATOR << 1 ---\n";
        std::cout << shifted.toString();

        shifted = original;
        shifted >> 1;

        std::cout << "\n--- OPERATOR >> 1 ---\n";
        std::cout << shifted.toString();
    }


    /**
     * @brief Запустить один полный пример с выбранным способом заполнения.
     */
    void runOneExample()
    {
        const std::size_t rows =
            readPositiveSize("Enter number of rows: ");

        const std::size_t columns =
            readPositiveSize("Enter number of columns: ");

        std::cout
            << "\nChoose matrix filling method:\n"
            << "1 - random numbers\n"
            << "2 - keyboard input\n"
            << "3 - zeros\n"
            << "4 - constant value\n";

        const int choice = readMenuChoice(
            "Your choice: ",
            1,
            4
        );

        if (choice == 1)
        {
            // Отдельно проверяем диапазон в ConsoleApp, чтобы пользователь
            // получил понятное сообщение сразу. RandomGenerator всё равно
            // имеет собственную внутреннюю проверку на случай использования
            // класса из другого кода.
            while (true)
            {
                const int minValue =
                    readInt("Random minimum: ");

                const int maxValue =
                    readInt("Random maximum: ");

                if (minValue <= maxValue)
                {
                    RandomGenerator generator(minValue, maxValue);
                    runTasks(rows, columns, generator);
                    break;
                }
                else
                {
                    std::cout
                        << "ERROR: minimum cannot be greater than maximum. "
                        << "Enter the range again.\n";
                }
            }
        }
        else if (choice == 2)
        {
            std::cout
                << "Enter exactly "
                << rows * columns
                << " integer values for the matrix.\n";

            IStreamGenerator generator(std::cin);
            runTasks(rows, columns, generator);
        }
        else if (choice == 3)
        {
            ZeroGenerator generator;
            runTasks(rows, columns, generator);
        }
        else if (choice == 4)
        {
            const int value =
                readInt("Enter constant value: ");

            ConstantGenerator generator(value);
            runTasks(rows, columns, generator);
        }
        else
        {
            // readMenuChoice() уже не позволяет сюда попасть.
            // Ветка оставлена как защитная проверка на случай будущих изменений.
            throw std::logic_error(
                "ConsoleApp: unexpected menu choice."
            );
        }
    }
}


int main()
{
    std::cout
        << "Variant 5. Matrix OOP demonstration.\n"
        << "All input errors are handled and reported.\n\n";

    bool continueProgram = true;

    while (continueProgram)
    {
        try
        {
            runOneExample();
        }
        catch (const std::invalid_argument& error)
        {
            std::cout
                << "\nERROR [invalid argument]: "
                << error.what()
                << '\n';
        }
        catch (const std::out_of_range& error)
        {
            std::cout
                << "\nERROR [out of range]: "
                << error.what()
                << '\n';
        }
        catch (const std::overflow_error& error)
        {
            std::cout
                << "\nERROR [integer overflow]: "
                << error.what()
                << '\n';
        }
        catch (const std::runtime_error& error)
        {
            std::cout
                << "\nERROR [runtime/input error]: "
                << error.what()
                << '\n';
        }
        catch (const std::bad_alloc&)
        {
            std::cout
                << "\nERROR: not enough memory for a matrix of this size.\n";
        }
        catch (const std::exception& error)
        {
            // Общий резервный обработчик стандартных исключений.
            std::cout
                << "\nERROR [standard exception]: "
                << error.what()
                << '\n';
        }
        catch (...)
        {
            // Самый последний резервный вариант для неизвестной ошибки.
            std::cout
                << "\nERROR: unknown unexpected error.\n";
        }

        std::cout
            << "\nRun another example?\n"
            << "1 - yes\n"
            << "0 - no\n";

        const int again = readMenuChoice(
            "Your choice: ",
            0,
            1
        );

        if (again == 1)
        {
            continueProgram = true;
            std::cout << '\n';
        }
        else
        {
            continueProgram = false;
        }
    }

    std::cout << "Program finished normally.\n";
    return 0;
}
