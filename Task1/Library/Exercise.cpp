#include "Exercise.h"

#include <stdexcept>

miit::algebra::Exercise::Exercise(
    std::size_t rows,
    std::size_t columns,
    Generator& generator
)
    : matrix(rows, columns),
      generator(generator)
{
    // Если generator выдаст ошибку, конструктор Exercise тоже завершится
    // исключением, и некорректный объект не будет создан.
    matrix.fill(generator);
}


miit::algebra::Exercise::Exercise(
    const Matrix<int>& matrix,
    Generator& generator
)
    : matrix(matrix),
      generator(generator)
{
    if (!matrix.isEmpty())
    {
        // Всё корректно, дополнительная работа не нужна.
    }
    else
    {
        throw std::invalid_argument(
            "Exercise: an empty matrix cannot be used for a task."
        );
    }
}


miit::algebra::Exercise::~Exercise() = default;


miit::algebra::Matrix<int>&
miit::algebra::Exercise::getMatrix()
{
    return matrix;
}


const miit::algebra::Matrix<int>&
miit::algebra::Exercise::getMatrix() const
{
    return matrix;
}
