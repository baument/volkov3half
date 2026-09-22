#include "RandomGenerator.h"

#include <stdexcept>

miit::algebra::RandomGenerator::RandomGenerator(int min, int max)
    : generator(std::random_device{}())
{
    // Диапазон [min, max] имеет смысл только если min <= max.
    if (min <= max)
    {
        distribution = std::uniform_int_distribution<int>(min, max);
    }
    else
    {
        // Library не печатает ошибку через cout: она сообщает о ней
        // вызывающему коду через исключение.
        throw std::invalid_argument(
            "RandomGenerator: minimum cannot be greater than maximum."
        );
    }
}

int miit::algebra::RandomGenerator::generate()
{
    return distribution(generator);
}
