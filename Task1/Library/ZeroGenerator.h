#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, который всегда возвращает 0.
     */
    class ZeroGenerator : public Generator
    {
    public:
        int generate() override;
    };
}
