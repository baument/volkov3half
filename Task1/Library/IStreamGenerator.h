#pragma once

#include "Generator.h"
#include <istream>

namespace miit::algebra
{
    /**
     * @brief Генератор, который читает числа из входного потока.
     *
     * В ConsoleApp ему можно передать std::cin.
     * В Tests ему можно передать std::istringstream.
     * Поэтому класс не привязан напрямую к клавиатуре.
     */
    class IStreamGenerator : public Generator
    {
    private:
        std::istream& in;

    public:
        /**
         * @brief Создать генератор, читающий из указанного потока.
         */
        explicit IStreamGenerator(std::istream& in);

        /**
         * @brief Прочитать следующее целое число.
         * @throws std::runtime_error Если из потока нельзя прочитать int.
         */
        int generate() override;
    };
}
