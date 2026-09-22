#include "Task1.h"

#include <limits>
#include <stdexcept>
#include <utility>

miit::algebra::Task1::Task1(
    std::size_t rows,
    std::size_t columns,
    Generator& generator
)
    : Exercise(rows, columns, generator)
{
}


miit::algebra::Task1::Task1(
    const Matrix<int>& matrix,
    Generator& generator
)
    : Exercise(matrix, generator)
{
}


void miit::algebra::Task1::solve()
{
    if (matrix.isEmpty())
    {
        // В нормальной работе сюда попасть нельзя, потому что Exercise
        // уже запрещает пустую матрицу. Проверка оставлена защитно.
        throw std::logic_error(
            "Task1::solve: matrix is empty."
        );
    }
    else
    {
        // Работаем с копией, чтобы при ошибке исходная матрица не была
        // изменена только наполовину.
        Matrix<int> result = matrix;

        for (std::size_t row = 0; row < result.rows(); ++row)
        {
            int maxValue = result.at(row, 0);

            // 1. Находим максимальное значение текущей строки.
            for (
                std::size_t column = 1;
                column < result.columns();
                ++column
            )
            {
                if (result.at(row, column) > maxValue)
                {
                    maxValue = result.at(row, column);
                }
                else
                {
                    // Текущий элемент не больше уже найденного максимума.
                    // Это нормальная ситуация, а не ошибка.
                }
            }

            // У int есть особый крайний случай: INT_MIN нельзя безопасно
            // превратить в положительное число простым -INT_MIN,
            // потому что положительный аналог не помещается в int.
            if (maxValue == std::numeric_limits<int>::min())
            {
                throw std::overflow_error(
                    "Task1::solve: cannot negate INT_MIN without overflow."
                );
            }
            else
            {
                // 2. Меняем знак у всех элементов, равных максимуму строки.
                for (
                    std::size_t column = 0;
                    column < result.columns();
                    ++column
                )
                {
                    if (result.at(row, column) == maxValue)
                    {
                        result.at(row, column) = -result.at(row, column);
                    }
                    else
                    {
                        // Остальные элементы строки оставляем как есть.
                    }
                }
            }
        }

        // Все строки обработаны без ошибок — только теперь сохраняем результат.
        matrix = std::move(result);
    }
}
