//
// Created by Dmitry Patsura on 2018-11-28.
//

#ifndef HLVM_RUNTIME_MACHINE_H
#define HLVM_RUNTIME_MACHINE_H

//#include "v8/src/base/utils/random-number-generator.h"
#include <stdint.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include "syscall_keystone.h"

/**
 * Store whole Runtime
 */

class KeystoneRNG {
public:
	uintptr_t generateRandomNumberUint() {
	    uintptr_t ret = SYSCALL_0(SYSCALL_GENRAND_WORD);
            return ret;
	}

	double NextDouble() {
	   uintptr_t ret = SYSCALL_0(SYSCALL_GENRAND_WORD);
	   //printf("Random: %llu\n", ret);
	   uintptr_t exponent = ret % 1023;
	   uintptr_t sign = 0;
	   uintptr_t mantissa = ret >> 12;
	   uintptr_t res_int = (exponent << 52) | mantissa;
	   double res;
	   memcpy(&res, &res_int, sizeof(double));
	   return res;
	}
};

class Machine {
protected:
    //v8::base::RandomNumberGenerator* randomNumberGenerator = nullptr;
    KeystoneRNG *rng = nullptr;
public:
    static Machine& Instance() {
        static Machine s;

        return s;
    }


    KeystoneRNG* getRandomNumberGenerator() {
        if (this->rng) {
            return this->rng;
        }

        return this->rng = new KeystoneRNG();
    }
private:
    Machine() { }
    ~Machine() { }

    Machine(Machine const&) = delete;
    Machine& operator= (Machine const&) = delete;
};


#endif //HLVM_RUNTIME_MACHINE_H
