#include "timing.h"

void get_monotonic_time(struct timespec* ts) {
    #ifdef __MACH__
        clock_serv_t cclock;
        mach_timespec_t mts;
        host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
        clock_get_time(cclock, &mts);
        mach_port_deallocate(mach_task_self(), cclock);
        ts->tv_sec = mts.tv_sec;
        ts->tv_nsec = mts.tv_nsec;
    #else
        clock_gettime(CLOCK_MONOTONIC, ts);
    #endif
}

double get_elapsed_time_ms(struct timespec* start, struct timespec* end) {
  double delta_s = end->tv_sec - start->tv_sec;
  double delta_ns = end->tv_nsec - start->tv_nsec;
  
  return delta_s * 1e3 + delta_ns * 1e-6;
}