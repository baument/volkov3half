#pragma once

#include "Generator.h"
#include <random>

namespace miit::algebra
{
    /**
     * @brief Генератор случайных целых чисел в диапазоне [min, max].
     */
    class RandomGenerator : public Generator
    {
    private:
        // Распределение задаёт допустимый диапазон случайных чисел.
        std::uniform_int_distribution<int> distribution;

        // Сам генератор псевдослучайных чисел.
        std::mt19937 generator;

    public:
        /**
         * @brief Создать генератор случайных чисел.
         * @param min Минимальное допустимое число.
         * @param max Максимальное допустимое число.
         * @throws std::invalid_argument Если min > max.
         */
        RandomGenerator(int min, int max);

        /**
         * @brief Получить очередное случайное число.
         */
        int generate() override;
    };
}
