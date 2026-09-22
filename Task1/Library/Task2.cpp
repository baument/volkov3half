#include "Task2.h"

#include <stdexcept>
#include <utility>
#include <vector>

miit::algebra::Task2::Task2(
    std::size_t rows,
    std::size_t columns,
    Generator& generator
)
    : Exercise(rows, columns, generator)
{
}


miit::algebra::Task2::Task2(
    const Matrix<int>& matrix,
    Generator& generator
)
    : Exercise(matrix, generator)
{
}


void miit::algebra::Task2::solve()
{
    if (matrix.isEmpty())
    {
        throw std::logic_error(
            "Task2::solve: matrix is empty."
        );
    }
    else
    {
        // 1. Находим глобальный максимум всей матрицы.
        int maxValue = matrix.at(0, 0);

        for (std::size_t row = 0; row < matrix.rows(); ++row)
        {
            for (
                std::size_t column = 0;
                column < matrix.columns();
                ++column
            )
            {
                if (matrix.at(row, column) > maxValue)
                {
                    maxValue = matrix.at(row, column);
                }
                else
                {
                    // Текущий элемент не больше максимума — ничего не меняем.
                }
            }
        }

        // 2. Запоминаем номера всех столбцов, где встретился maxValue.
        std::vector<std::size_t> columnsWithMax;

        for (
            std::size_t column = 0;
            column < matrix.columns();
            ++column
        )
        {
            bool containsMax = false;

            for (std::size_t row = 0; row < matrix.rows(); ++row)
            {
                if (matrix.at(row, column) == maxValue)
                {
                    containsMax = true;
                    break;
                }
                else
                {
                    // В этой строке максимума нет — проверяем следующую.
                }
            }

            if (containsMax)
            {
                // Даже если максимум встречается в одном столбце несколько раз,
                // номер столбца добавляется только один раз.
                columnsWithMax.push_back(column);
            }
            else
            {
                // В этом столбце глобального максимума нет.
            }
        }

        // Для непустой матрицы хотя бы один столбец обязан содержать максимум.
        // Если список вдруг пуст, значит нарушилась внутренняя логика программы.
        if (columnsWithMax.empty())
        {
            throw std::logic_error(
                "Task2::solve: internal error, maximum column was not found."
            );
        }
        else
        {
            Matrix<int> result = matrix;

            // Вставляем справа налево.
            // Иначе вставка слева изменила бы индексы ещё не обработанных
            // столбцов справа.
            for (std::size_t i = columnsWithMax.size(); i > 0; --i)
            {
                result.insertColumnAfter(
                    columnsWithMax[i - 1],
                    0
                );
            }

            matrix = std::move(result);
        }
    }
}
