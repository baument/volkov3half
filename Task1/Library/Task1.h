#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Вариант 5, задание 1.
     *
     * В каждой строке найти максимальное значение и заменить все элементы,
     * равные этому максимуму, на противоположные по знаку.
     *
     * Если максимум встречается несколько раз, меняются все такие элементы.
     * Это поведение явно выбрано и проверяется тестами.
     */
    class Task1 : public Exercise
    {
    public:
        Task1(
            std::size_t rows,
            std::size_t columns,
            Generator& generator
        );

        Task1(
            const Matrix<int>& matrix,
            Generator& generator
        );

        void solve() override;
    };
}
