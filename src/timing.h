#ifndef _TIMING_H
#define _TIMING_H

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#ifdef __MACH__
  #include <mach/clock.h>
  #include <mach/mach.h>
#endif

// Get a nanosecond-precise time in both Linux and Mac OS X.
void get_monotonic_time(struct timespec* ts);

// Compute the difference between time instants, in milliseconds.
double get_elapsed_time_ms(struct timespec* start, struct timespec* end);

#endif