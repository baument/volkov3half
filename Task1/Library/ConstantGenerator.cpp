#include "ConstantGenerator.h"

miit::algebra::ConstantGenerator::ConstantGenerator(int value)
    : value(value)
{
}

int miit::algebra::ConstantGenerator::generate()
{
    return value;
}
