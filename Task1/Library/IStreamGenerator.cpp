#include "IStreamGenerator.h"

#include <limits>
#include <stdexcept>

miit::algebra::IStreamGenerator::IStreamGenerator(std::istream& in)
    : in(in)
{
}

int miit::algebra::IStreamGenerator::generate()
{
    int value = 0;

    if (in >> value)
    {
        // Число успешно прочитано.
        return value;
    }
    else
    {
        // Поток попал в состояние ошибки, например пользователь ввёл "abc".
        // Сбрасываем флаг ошибки и удаляем неправильный остаток строки,
        // чтобы поток можно было использовать дальше.
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        throw std::runtime_error(
            "IStreamGenerator: expected an integer value."
        );
    }
}
