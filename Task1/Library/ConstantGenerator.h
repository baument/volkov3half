#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, который всегда возвращает одну заданную константу.
     */
    class ConstantGenerator : public Generator
    {
    private:
        int value;

    public:
        explicit ConstantGenerator(int value);

        int generate() override;
    };
}
