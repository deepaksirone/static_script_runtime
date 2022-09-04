#include "time.h"
#include "syscall_keystone.h"
#include <stdint.h>

static uint64_t get_unix_time() {
	uint64_t epoch_seconds = SYSCALL_0(SYSCALL_GET_TIME);
	return epoch_seconds;
}

LIBRARY_EXPORT double Time__hour() {	
	time_t t = get_unix_time();
	struct tm *time = gmtime((const time_t *)&t);

	return (double)(time->tm_hour);
}
LIBRARY_EXPORT double Time__day() {
	time_t t = get_unix_time();
        struct tm *time = gmtime((const time_t *)&t);
	
	return (double)(time->tm_wday);
}

LIBRARY_EXPORT double Time__second() {
	time_t t = get_unix_time();
        struct tm *time = gmtime((const time_t *)&t);

        return (double)(time->tm_sec);
}

LIBRARY_EXPORT double Time__month() {
        time_t t = get_unix_time();
        struct tm *time = gmtime((const time_t *)&t);

        return (double)(time->tm_mon);
}

LIBRARY_EXPORT double Time__year() {
        time_t t = get_unix_time();
        struct tm *time = gmtime((const time_t *)&t);

        return (double)(time->tm_year + 1900);
}

