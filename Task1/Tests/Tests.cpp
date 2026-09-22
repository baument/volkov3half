#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"
#include "ZeroGenerator.h"

#include <cassert>
#include <climits>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace miit::algebra;

namespace
{
    void printTestPassed(const char* name)
    {
        std::cout << "[OK] " << name << '\n';
    }


    void testGenerators()
    {
        Matrix<int> matrix(2, 3);

        ConstantGenerator constantGenerator(5);
        matrix.fill(constantGenerator);

        for (std::size_t row = 0; row < matrix.rows(); ++row)
        {
            for (std::size_t column = 0; column < matrix.columns(); ++column)
            {
                assert(matrix.at(row, column) == 5);
            }
        }

        ZeroGenerator zeroGenerator;
        matrix.fill(zeroGenerator);

        for (std::size_t row = 0; row < matrix.rows(); ++row)
        {
            for (std::size_t column = 0; column < matrix.columns(); ++column)
            {
                assert(matrix.at(row, column) == 0);
            }
        }

        printTestPassed("generators: constant and zero");
    }


    void testTask1NormalAndNegativeValues()
    {
        Matrix<int> matrix(3, 4);

        matrix.at(0, 0) = 1;
        matrix.at(0, 1) = 7;
        matrix.at(0, 2) = 2;
        matrix.at(0, 3) = 4;

        matrix.at(1, 0) = -5;
        matrix.at(1, 1) = -2;
        matrix.at(1, 2) = -8;
        matrix.at(1, 3) = -3;

        matrix.at(2, 0) = 0;
        matrix.at(2, 1) = 1;
        matrix.at(2, 2) = 9;
        matrix.at(2, 3) = 3;

        ZeroGenerator generator;
        Task1 task(matrix, generator);
        task.solve();

        assert(task.getMatrix().at(0, 1) == -7);
        assert(task.getMatrix().at(1, 1) == 2);
        assert(task.getMatrix().at(2, 2) == -9);

        printTestPassed("Task1: normal and all-negative rows");
    }


    void testTask1DuplicateMaximums()
    {
        Matrix<int> matrix(2, 4);

        // В первой строке максимум 9 встречается два раза.
        matrix.at(0, 0) = 9;
        matrix.at(0, 1) = 1;
        matrix.at(0, 2) = 9;
        matrix.at(0, 3) = 2;

        // Во второй строке максимум -1 тоже встречается два раза.
        matrix.at(1, 0) = -1;
        matrix.at(1, 1) = -5;
        matrix.at(1, 2) = -1;
        matrix.at(1, 3) = -3;

        ZeroGenerator generator;
        Task1 task(matrix, generator);
        task.solve();

        // По принятому в проекте правилу меняются ВСЕ максимумы строки.
        assert(task.getMatrix().at(0, 0) == -9);
        assert(task.getMatrix().at(0, 2) == -9);
        assert(task.getMatrix().at(1, 0) == 1);
        assert(task.getMatrix().at(1, 2) == 1);

        printTestPassed("Task1: duplicate maximum values");
    }


    void testTask2SeveralMaximumColumns()
    {
        Matrix<int> matrix(3, 4);

        matrix.at(0, 0) = 1;
        matrix.at(0, 1) = 9;
        matrix.at(0, 2) = 2;
        matrix.at(0, 3) = 4;

        matrix.at(1, 0) = 3;
        matrix.at(1, 1) = 5;
        matrix.at(1, 2) = 9;
        matrix.at(1, 3) = 0;

        matrix.at(2, 0) = 8;
        matrix.at(2, 1) = 7;
        matrix.at(2, 2) = 6;
        matrix.at(2, 3) = 9;

        ZeroGenerator generator;
        Task2 task(matrix, generator);
        task.solve();

        const Matrix<int>& result = task.getMatrix();

        // Максимум 9 есть в столбцах 1, 2 и 3.
        // Было 4 столбца, стало 7.
        assert(result.rows() == 3);
        assert(result.columns() == 7);

        // Проверяем первую строку: 1 9 0 2 0 4 0
        assert(result.at(0, 0) == 1);
        assert(result.at(0, 1) == 9);
        assert(result.at(0, 2) == 0);
        assert(result.at(0, 3) == 2);
        assert(result.at(0, 4) == 0);
        assert(result.at(0, 5) == 4);
        assert(result.at(0, 6) == 0);

        printTestPassed("Task2: maximum occurs in several columns");
    }


    void testSingleElementMatrix()
    {
        Matrix<int> matrix(1, 1);
        matrix.at(0, 0) = 5;

        ZeroGenerator generator;

        Task1 task1(matrix, generator);
        task1.solve();
        assert(task1.getMatrix().at(0, 0) == -5);

        Task2 task2(matrix, generator);
        task2.solve();
        assert(task2.getMatrix().rows() == 1);
        assert(task2.getMatrix().columns() == 2);
        assert(task2.getMatrix().at(0, 0) == 5);
        assert(task2.getMatrix().at(0, 1) == 0);

        printTestPassed("1x1 matrix");
    }


    void testShiftOperators()
    {
        Matrix<int> matrix(2, 3);

        matrix.at(0, 0) = 1;
        matrix.at(0, 1) = 2;
        matrix.at(0, 2) = 3;
        matrix.at(1, 0) = 4;
        matrix.at(1, 1) = 5;
        matrix.at(1, 2) = 6;

        matrix << 1;
        assert(matrix.at(0, 0) == 2);
        assert(matrix.at(0, 1) == 3);
        assert(matrix.at(0, 2) == 1);

        matrix >> 1;
        assert(matrix.at(0, 0) == 1);
        assert(matrix.at(0, 1) == 2);
        assert(matrix.at(0, 2) == 3);

        // Сдвиг на 3 при трёх столбцах эквивалентен сдвигу на 0.
        matrix << 3;
        assert(matrix.at(0, 0) == 1);
        assert(matrix.at(0, 1) == 2);
        assert(matrix.at(0, 2) == 3);

        printTestPassed("shift operators, including full-cycle shift");
    }


    void testCopyAndAssignment()
    {
        Matrix<int> original(1, 2);
        original.at(0, 0) = 10;
        original.at(0, 1) = 20;

        // Конструктор копирования.
        Matrix<int> copy(original);
        assert(copy.at(0, 0) == 10);
        assert(copy.at(0, 1) == 20);

        // Оператор присваивания.
        Matrix<int> assigned(1, 2);
        assigned = original;
        assert(assigned.at(0, 0) == 10);
        assert(assigned.at(0, 1) == 20);

        // Самоприсваивание не должно ломать объект.
        assigned = assigned;
        assert(assigned.at(0, 0) == 10);
        assert(assigned.at(0, 1) == 20);

        printTestPassed("copy constructor and assignment operator");
    }


    void testErrorZeroMatrixSize()
    {
        bool errorCaught = false;

        try
        {
            Matrix<int> invalidMatrix(0, 3);
            (void)invalidMatrix;
        }
        catch (const std::invalid_argument& error)
        {
            errorCaught = true;
            std::cout
                << "[EXPECTED ERROR] zero matrix size: "
                << error.what()
                << '\n';
        }
        catch (...)
        {
            assert(false && "Wrong exception type for zero matrix size");
        }

        assert(errorCaught);
    }


    void testErrorRandomRange()
    {
        bool errorCaught = false;

        try
        {
            RandomGenerator invalidGenerator(10, -10);
            (void)invalidGenerator;
        }
        catch (const std::invalid_argument& error)
        {
            errorCaught = true;
            std::cout
                << "[EXPECTED ERROR] invalid random range: "
                << error.what()
                << '\n';
        }
        catch (...)
        {
            assert(false && "Wrong exception type for random range");
        }

        assert(errorCaught);
    }


    void testErrorRowOutOfRange()
    {
        Matrix<int> matrix(2, 2);
        bool errorCaught = false;

        try
        {
            matrix[10][0] = 1;
        }
        catch (const std::out_of_range& error)
        {
            errorCaught = true;
            std::cout
                << "[EXPECTED ERROR] invalid row index: "
                << error.what()
                << '\n';
        }
        catch (...)
        {
            assert(false && "Wrong exception type for row index");
        }

        assert(errorCaught);
    }


    void testErrorColumnOutOfRange()
    {
        Matrix<int> matrix(2, 2);
        bool errorCaught = false;

        try
        {
            matrix.at(0, 10) = 1;
        }
        catch (const std::out_of_range& error)
        {
            errorCaught = true;
            std::cout
                << "[EXPECTED ERROR] invalid column index: "
                << error.what()
                << '\n';
        }
        catch (...)
        {
            assert(false && "Wrong exception type for column index");
        }

        assert(errorCaught);
    }


    void testErrorInsertInvalidColumn()
    {
        Matrix<int> matrix(2, 2);
        bool errorCaught = false;

        try
        {
            matrix.insertColumnAfter(5, 0);
        }
        catch (const std::out_of_range& error)
        {
            errorCaught = true;
            std::cout
                << "[EXPECTED ERROR] insert after invalid column: "
                << error.what()
                << '\n';
        }
        catch (...)
        {
            assert(false && "Wrong exception type for insertColumnAfter");
        }

        assert(errorCaught);
    }


    void testErrorBadStreamInputAndStrongFill()
    {
        // Исходно матрица полностью состоит из 7.
        Matrix<int> matrix(2, 2, 7);

        // Первое значение корректное, второе — текст, т.е. ошибка.
        std::istringstream input("1 wrong 3 4");
        IStreamGenerator generator(input);

        bool errorCaught = false;

        try
        {
            matrix.fill(generator);
        }
        catch (const std::runtime_error& error)
        {
            errorCaught = true;
            std::cout
                << "[EXPECTED ERROR] bad stream input: "
                << error.what()
                << '\n';
        }
        catch (...)
        {
            assert(false && "Wrong exception type for stream input");
        }

        assert(errorCaught);

        // Важно: fill() использует временную копию, поэтому даже после ошибки
        // матрица не осталась частично заполненной значениями 1, ...
        assert(matrix.at(0, 0) == 7);
        assert(matrix.at(0, 1) == 7);
        assert(matrix.at(1, 0) == 7);
        assert(matrix.at(1, 1) == 7);

        printTestPassed("fill keeps original matrix unchanged after input error");
    }


    void testErrorEmptyMatrixOperations()
    {
        Matrix<int> empty;

        bool shiftErrorCaught = false;
        try
        {
            empty << 1;
        }
        catch (const std::logic_error& error)
        {
            shiftErrorCaught = true;
            std::cout
                << "[EXPECTED ERROR] shift empty matrix: "
                << error.what()
                << '\n';
        }
        catch (...)
        {
            assert(false && "Wrong exception type for empty shift");
        }
        assert(shiftErrorCaught);

        ZeroGenerator generator;
        bool exerciseErrorCaught = false;

        try
        {
            Task1 task(empty, generator);
            (void)task;
        }
        catch (const std::invalid_argument& error)
        {
            exerciseErrorCaught = true;
            std::cout
                << "[EXPECTED ERROR] Task1 with empty matrix: "
                << error.what()
                << '\n';
        }
        catch (...)
        {
            assert(false && "Wrong exception type for empty task matrix");
        }
        assert(exerciseErrorCaught);
    }


    void testErrorIntMinInTask1()
    {
        Matrix<int> matrix(1, 2);
        matrix.at(0, 0) = INT_MIN;
        matrix.at(0, 1) = INT_MIN;

        ZeroGenerator generator;
        Task1 task(matrix, generator);

        bool errorCaught = false;

        try
        {
            task.solve();
        }
        catch (const std::overflow_error& error)
        {
            errorCaught = true;
            std::cout
                << "[EXPECTED ERROR] INT_MIN negation: "
                << error.what()
                << '\n';
        }
        catch (...)
        {
            assert(false && "Wrong exception type for INT_MIN");
        }

        assert(errorCaught);

        // solve() работал с копией, поэтому исходная матрица задания
        // после ошибки осталась неизменной.
        assert(task.getMatrix().at(0, 0) == INT_MIN);
        assert(task.getMatrix().at(0, 1) == INT_MIN);

        printTestPassed("Task1 keeps matrix unchanged after overflow error");
    }
}


int main()
{
    std::cout << "=== NORMAL CASES ===\n";

    testGenerators();
    testTask1NormalAndNegativeValues();
    testTask1DuplicateMaximums();
    testTask2SeveralMaximumColumns();
    testSingleElementMatrix();
    testShiftOperators();
    testCopyAndAssignment();

    std::cout << "\n=== EXPECTED ERROR CASES ===\n";

    testErrorZeroMatrixSize();
    testErrorRandomRange();
    testErrorRowOutOfRange();
    testErrorColumnOutOfRange();
    testErrorInsertInvalidColumn();
    testErrorBadStreamInputAndStrongFill();
    testErrorEmptyMatrixOperations();
    testErrorIntMinInTask1();

    std::cout << "\nALL TESTS PASSED.\n";
    return 0;
}
