#include <stdio.h>
#include "library.h"
#include "syscall_keystone.h"


static uint64_t get_unix_time() {
	uint64_t epoch_seconds = SYSCALL_0(SYSCALL_GET_TIME);
	return epoch_seconds;
}


C_LIBRARY_EXPORT double Meta_currentUserTime_hour() {
    uint64_t unix_time = get_unix_time();
    //uint64_t seconds_in_normal_year = 365 * 24 * 60 * 60;
    //uint64_t tot_years = unix_time / (seconds_in_normal_year);
    uint64_t seconds_in_day = 24 * 60 * 60;
    uint64_t second_offset_in_day = unix_time % seconds_in_day;
    uint64_t hour = second_offset_in_day / (60 * 60);

    //printf("[DEBUG] Meta_currentUserTime_hour: %lu\n", hour);
    return (double)hour;
}

C_LIBRARY_EXPORT double Meta_currentUserTime_minute() {
    uint64_t unix_time = get_unix_time();
    uint64_t seconds_in_day = 24 * 60 * 60;
    uint64_t second_offset_in_day = unix_time % seconds_in_day;
    uint64_t seconds_past_hour = second_offset_in_day % (60 * 60);
    uint64_t minut = seconds_past_hour / 60;
    return minut;
}

C_LIBRARY_EXPORT double Meta_currentUserTime_month() {
    uint64_t unix_time = get_unix_time();

    uint64_t seconds_in_normal_year = 365 * 24 * 60 * 60;
    uint64_t tot_years = unix_time / (seconds_in_normal_year);

    uint64_t seconds_elapsed_in_year = unix_time % seconds_in_normal_year;
    // Ignores leap years and non 30 day months
    uint64_t seconds_in_month = (30 * 24 * 60 * 60);
    uint64_t month = (seconds_elapsed_in_year / seconds_in_month);
    return month;
}

