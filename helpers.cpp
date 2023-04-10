#include <stdio.h>
#include <stdlib.h>

//#include "helpers.h"
#include "library.h"

LIBRARY_EXPORT const char* number2string(double number) {
    char* result = (char *)malloc(100);

    snprintf(result, 100, "%f", number);

    return result;
}

C_LIBRARY_EXPORT double parseInt(const char *str) {
    double ret;
    sscanf(str, "%lf", &ret);
    return ret;
}

C_LIBRARY_EXPORT double parseFloat(const char *str) {
    return parseInt(str);
}

char *moment_worker(moment_t *moment) {
    char *res = (char *)malloc(101);
    snprintf(res, 100, "%d %d %d %d:%d:%d", moment->day, moment->month, moment->year, moment->hour, moment->minute, moment->second);
    return res;
}


C_LIBRARY_EXPORT char * moment_toString() {
    moment_t moment;
    moment.day = 10;
    moment.month = 10;
    moment.year = 2022;
    moment.hour = 12;
    moment.minute = 10;
    moment.second = 10;

    return moment_worker(&moment);
}

LIBRARY_EXPORT void console_log(double number) {
    puts(number2string(number));
}

LIBRARY_EXPORT void console_log(const char *str) {
    puts(str);
}

LIBRARY_EXPORT void console_log(bool boolean) {
    if (boolean) {
        puts("true");
    } else {
        puts("false");
    }
}

extern "C" LIBRARY_EXPORT void skip() {
	return;
}
