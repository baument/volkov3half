#pragma once

#include "Generator.h"
#include "Matrix.h"

#include <cstddef>

namespace miit::algebra
{
    /**
     * @brief Абстрактный базовый класс для заданий варианта.
     *
     * Он хранит Matrix и ссылку на Generator, как требует условие.
     * Конкретный алгоритм задаётся в Task1 и Task2 через solve().
     */
    class Exercise
    {
    protected:
        // protected позволяет наследникам Task1 и Task2 работать с matrix.
        Matrix<int> matrix;

        // Ссылка: новый Generator здесь не создаётся, используется уже
        // существующий объект конкретного наследника.
        Generator& generator;

    public:
        /**
         * @brief Создать новую матрицу и заполнить её генератором.
         */
        Exercise(
            std::size_t rows,
            std::size_t columns,
            Generator& generator
        );

        /**
         * @brief Создать Exercise на основе уже готовой матрицы.
         * @throws std::invalid_argument Если передана пустая матрица.
         */
        Exercise(
            const Matrix<int>& matrix,
            Generator& generator
        );

        virtual ~Exercise();

        /**
         * @brief Выполнить конкретное задание.
         * Чисто виртуальный метод: реализация есть только у наследников.
         */
        virtual void solve() = 0;

        /** @brief Получить изменяемую матрицу. */
        Matrix<int>& getMatrix();

        /** @brief Получить матрицу только для чтения. */
        const Matrix<int>& getMatrix() const;
    };
}
