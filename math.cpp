#include <cmath>

#include "math.h"
#if defined (__riscv)
#include "machine_riscv.h"
#else
#include "machine.h"
#endif

LIBRARY_EXPORT double Math__abs(double number) {
    return std::abs(number);
}

LIBRARY_EXPORT double Math__pow(double number, double power) {
    return std::pow(number, power);
}

LIBRARY_EXPORT double Math__sqrt(double number) {
    return std::sqrt(number);
}

LIBRARY_EXPORT double Math__floor(double number) {
    return std::floor(number);
}

LIBRARY_EXPORT double Math__round(double number) {
    return std::round(number);
}

LIBRARY_EXPORT double Math__random() {
    return Machine::Instance().getRandomNumberGenerator()->NextDouble();
}

struct TypedDoubleArray {
    void *start;
    int32_t size;
};

LIBRARY_EXPORT void* Array__constructor(double size) {
    auto *ptr = new TypedDoubleArray();
    ptr->size = (int32_t)size;
    ptr->start = new double[(int32_t)size];

    return ptr;
}

LIBRARY_EXPORT double Array__push(void *ptr, double number) {
    auto *left = static_cast<TypedDoubleArray*>(ptr);

    left->size++;
    realloc(left, left->size * sizeof(double));

    return left->size;
}
