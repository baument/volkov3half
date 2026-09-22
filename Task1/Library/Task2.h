#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Вариант 5, задание 2.
     *
     * Найти максимальное значение всей матрицы. После каждого столбца,
     * в котором это значение встречается хотя бы один раз, вставить
     * один столбец из нулей.
     */
    class Task2 : public Exercise
    {
    public:
        Task2(
            std::size_t rows,
            std::size_t columns,
            Generator& generator
        );

        Task2(
            const Matrix<int>& matrix,
            Generator& generator
        );

        void solve() override;
    };
}
