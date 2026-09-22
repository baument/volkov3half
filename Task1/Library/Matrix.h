#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace miit::algebra
{
    class Generator;

    /**
     * @brief Шаблонный класс двумерной матрицы.
     *
     * T — тип элементов. В данной лабораторной используется Matrix<int>,
     * потому что по условию массив состоит из целых чисел.
     */
    template <typename T>
    class Matrix
    {
    private:
        // Внешний vector хранит строки, внутренний — элементы строки.
        std::vector<std::vector<T>> data;

    public:
        /**
         * @brief Конструктор по умолчанию.
         * Создаёт пустую матрицу. Он нужен по требованию задания.
         */
        Matrix();

        /**
         * @brief Создать прямоугольную матрицу rows x columns.
         * @param value Начальное значение каждого элемента.
         * @throws std::invalid_argument Если rows == 0 или columns == 0.
         */
        Matrix(
            std::size_t rows,
            std::size_t columns,
            const T& value = T{}
        );

        /** @brief Конструктор копирования. */
        Matrix(const Matrix& other);

        /** @brief Конструктор перемещения. */
        Matrix(Matrix&& other) noexcept;

        /** @brief Деструктор. */
        ~Matrix();

        /** @brief Оператор копирующего присваивания. */
        Matrix& operator=(const Matrix& other);

        /** @brief Оператор перемещающего присваивания. */
        Matrix& operator=(Matrix&& other) noexcept;

        /**
         * @brief Получить строку по индексу.
         * @throws std::out_of_range Если строки с таким индексом нет.
         *
         * Нужен по требованию задания для доступа вида matrix[row][column].
         */
        std::vector<T>& operator[](std::size_t row);

        /** @brief Const-версия operator[]. */
        const std::vector<T>& operator[](std::size_t row) const;

        /**
         * @brief Безопасный доступ сразу по строке и столбцу.
         * @throws std::out_of_range При неверном row или column.
         *
         * Внутри алгоритмов используется именно at(), чтобы проверять
         * обе координаты, а не только номер строки.
         */
        T& at(std::size_t row, std::size_t column);

        /** @brief Const-версия at(). */
        const T& at(std::size_t row, std::size_t column) const;

        /**
         * @brief Циклически сдвинуть каждую строку влево.
         * @throws std::logic_error Если матрица пустая.
         */
        Matrix& operator<<(std::size_t shift);

        /**
         * @brief Циклически сдвинуть каждую строку вправо.
         * @throws std::logic_error Если матрица пустая.
         */
        Matrix& operator>>(std::size_t shift);

        /** @brief Количество строк. */
        std::size_t rows() const;

        /** @brief Количество столбцов. */
        std::size_t columns() const;

        /** @brief Проверить, пустая ли матрица. */
        bool isEmpty() const;

        /**
         * @brief Заполнить матрицу значениями из Generator.
         * @throws std::logic_error Если матрица пустая.
         *
         * Если Generator выдаст ошибку в середине заполнения,
         * исходная матрица останется неизменной.
         */
        void fill(Generator& generator);

        /**
         * @brief Вставить новый столбец после указанного.
         * @throws std::logic_error Если матрица пустая.
         * @throws std::out_of_range Если column не существует.
         */
        void insertColumnAfter(
            std::size_t column,
            const T& value
        );

        /**
         * @brief Получить матрицу в виде строки для последующего вывода.
         * Library сама ничего не печатает в консоль.
         */
        std::string toString() const;
    };
}
