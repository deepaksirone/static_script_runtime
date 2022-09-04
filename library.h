
#ifndef HLVM_RUNTIME_HELPERS_H
#define HLVM_RUNTIME_HELPERS_H

#define LIBRARY_EXPORT __attribute__ ((visibility ("default")))
#define C_LIBRARY_EXPORT extern "C" LIBRARY_EXPORT
#define CRYPT_CODE __attribute__((section(".secure_code")))
#define CRYPT_CODE_LIBRARY_EXPORT __attribute__((section(".secure_code"), visibility("default")))
#define CRYPT_DATA __attribute__((section(".secure_data")))

#endif //HLVM_RUNTIME_HELPERS_H
