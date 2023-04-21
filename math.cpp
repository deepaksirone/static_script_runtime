#include <cmath>

#include "library.h"
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

C_LIBRARY_EXPORT double Math_floor(double number) {
    return Math__floor(number);
}

LIBRARY_EXPORT double Math__random() {
    return Machine::Instance().getRandomNumberGenerator()->NextDouble();
}

C_LIBRARY_EXPORT double Math_random() {
    return Math__random();
}

C_LIBRARY_EXPORT char *_Z15Number__toFixedd(double num, double fix) {
    //TODO: Add support for more decimal places
    char* result = (char *)malloc(20);

    snprintf(result, 100, "%.1f", num);
    return result;

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
