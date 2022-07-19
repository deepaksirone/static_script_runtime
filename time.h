//
// Created by Dmitry Patsura on 2018-11-18.
//

#include "library.h"
#include <time.h>

#ifndef HLVM_RUNTIME_TIME_H
#define HLVM_RUNTIME_TIME_H

LIBRARY_EXPORT double Time__hour();
LIBRARY_EXPORT double Time__day();
LIBRARY_EXPORT double Time__second();
LIBRARY_EXPORT double Time__month();
LIBRARY_EXPORT double Time__year();

#endif //HLVM_RUNTIME_MATH_H
