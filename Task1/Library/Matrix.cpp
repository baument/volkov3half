#include "Matrix.h"
#include "Generator.h"

#include <sstream>
#include <stdexcept>
#include <utility>

namespace miit::algebra
{
    template <typename T>
    Matrix<T>::Matrix() = default;


    template <typename T>
    Matrix<T>::Matrix(
        std::size_t rows,
        std::size_t columns,
        const T& value
    )
    {
        if (rows > 0 && columns > 0)
        {
            data = std::vector<std::vector<T>>(
                rows,
                std::vector<T>(columns, value)
            );
        }
        else
        {
            // Матрица 0 x N или N x 0 для данной работы считается ошибкой.
            throw std::invalid_argument(
                "Matrix: rows and columns must be greater than zero."
            );
        }
    }


    template <typename T>
    Matrix<T>::Matrix(const Matrix& other)
        : data(other.data)
    {
    }


    template <typename T>
    Matrix<T>::Matrix(Matrix&& other) noexcept
        : data(std::move(other.data))
    {
    }


    template <typename T>
    Matrix<T>::~Matrix() = default;


    template <typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& other)
    {
        if (this != &other)
        {
            data = other.data;
        }
        else
        {
            // Самоприсваивание (matrix = matrix) допустимо.
            // Ничего делать не нужно, потому что данные уже находятся
            // в правильном объекте.
        }

        return *this;
    }


    template <typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
    {
        if (this != &other)
        {
            data = std::move(other.data);
        }
        else
        {
            // Самоперемещение тоже просто оставляем без изменений.
        }

        return *this;
    }


    template <typename T>
    std::vector<T>& Matrix<T>::operator[](std::size_t row)
    {
        if (row < rows())
        {
            return data[row];
        }
        else
        {
            throw std::out_of_range(
                "Matrix::operator[]: row index is out of range."
            );
        }
    }


    template <typename T>
    const std::vector<T>& Matrix<T>::operator[](std::size_t row) const
    {
        if (row < rows())
        {
            return data[row];
        }
        else
        {
            throw std::out_of_range(
                "Matrix::operator[] const: row index is out of range."
            );
        }
    }


    template <typename T>
    T& Matrix<T>::at(std::size_t row, std::size_t column)
    {
        if (row >= rows())
        {
            throw std::out_of_range(
                "Matrix::at: row index is out of range."
            );
        }
        else if (column >= columns())
        {
            throw std::out_of_range(
                "Matrix::at: column index is out of range."
            );
        }
        else
        {
            return data[row][column];
        }
    }


    template <typename T>
    const T& Matrix<T>::at(std::size_t row, std::size_t column) const
    {
        if (row >= rows())
        {
            throw std::out_of_range(
                "Matrix::at const: row index is out of range."
            );
        }
        else if (column >= columns())
        {
            throw std::out_of_range(
                "Matrix::at const: column index is out of range."
            );
        }
        else
        {
            return data[row][column];
        }
    }


    template <typename T>
    Matrix<T>& Matrix<T>::operator<<(std::size_t shift)
    {
        if (isEmpty())
        {
            throw std::logic_error(
                "Matrix::operator<<: cannot shift an empty matrix."
            );
        }
        else
        {
            // Сдвиг на число, кратное количеству столбцов, ничего не меняет.
            shift %= columns();

            if (shift == 0)
            {
                return *this;
            }
            else
            {
                for (std::size_t row = 0; row < rows(); ++row)
                {
                    for (std::size_t step = 0; step < shift; ++step)
                    {
                        const T first = data[row][0];

                        for (
                            std::size_t column = 0;
                            column + 1 < columns();
                            ++column
                        )
                        {
                            data[row][column] = data[row][column + 1];
                        }

                        data[row][columns() - 1] = first;
                    }
                }
            }
        }

        return *this;
    }


    template <typename T>
    Matrix<T>& Matrix<T>::operator>>(std::size_t shift)
    {
        if (isEmpty())
        {
            throw std::logic_error(
                "Matrix::operator>>: cannot shift an empty matrix."
            );
        }
        else
        {
            shift %= columns();

            if (shift == 0)
            {
                return *this;
            }
            else
            {
                for (std::size_t row = 0; row < rows(); ++row)
                {
                    for (std::size_t step = 0; step < shift; ++step)
                    {
                        const T last = data[row][columns() - 1];

                        for (
                            std::size_t column = columns() - 1;
                            column > 0;
                            --column
                        )
                        {
                            data[row][column] = data[row][column - 1];
                        }

                        data[row][0] = last;
                    }
                }
            }
        }

        return *this;
    }


    template <typename T>
    std::size_t Matrix<T>::rows() const
    {
        return data.size();
    }


    template <typename T>
    std::size_t Matrix<T>::columns() const
    {
        if (data.empty())
        {
            return 0;
        }
        else
        {
            return data[0].size();
        }
    }


    template <typename T>
    bool Matrix<T>::isEmpty() const
    {
        return rows() == 0 || columns() == 0;
    }


    template <typename T>
    void Matrix<T>::fill(Generator& generator)
    {
        if (isEmpty())
        {
            throw std::logic_error(
                "Matrix::fill: cannot fill an empty matrix."
            );
        }
        else
        {
            // Заполняем временную копию.
            // Если generator.generate() бросит исключение на каком-то элементе,
            // исходная матрица не окажется заполненной только наполовину.
            Matrix<T> result(*this);

            for (std::size_t row = 0; row < rows(); ++row)
            {
                for (std::size_t column = 0; column < columns(); ++column)
                {
                    result.data[row][column] =
                        static_cast<T>(generator.generate());
                }
            }

            *this = std::move(result);
        }
    }


    template <typename T>
    void Matrix<T>::insertColumnAfter(
        std::size_t column,
        const T& value
    )
    {
        if (isEmpty())
        {
            throw std::logic_error(
                "Matrix::insertColumnAfter: matrix is empty."
            );
        }
        else if (column >= columns())
        {
            throw std::out_of_range(
                "Matrix::insertColumnAfter: column index is out of range."
            );
        }
        else
        {
            for (std::size_t row = 0; row < rows(); ++row)
            {
                data[row].insert(
                    data[row].begin()
                        + static_cast<std::ptrdiff_t>(column + 1),
                    value
                );
            }
        }
    }


    template <typename T>
    std::string Matrix<T>::toString() const
    {
        if (isEmpty())
        {
            // Это не ошибка: пустой объект можно безопасно представить строкой.
            return "[empty matrix]\n";
        }
        else
        {
            std::ostringstream out;

            for (std::size_t row = 0; row < rows(); ++row)
            {
                for (std::size_t column = 0; column < columns(); ++column)
                {
                    out << data[row][column];

                    if (column + 1 < columns())
                    {
                        out << '\t';
                    }
                    else
                    {
                        // После последнего элемента строки табуляция не нужна.
                    }
                }

                out << '\n';
            }

            return out.str();
        }
    }

    // В этой лабораторной по условию используются целые числа,
    // поэтому явно создаём реализацию шаблона для Matrix<int>.
    template class Matrix<int>;
}
