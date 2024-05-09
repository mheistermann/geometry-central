#pragma once

#include <chrono>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iomanip>

#define NOW (std::chrono::steady_clock::now())
#define START_TIMING(name) auto generated_timer_777_##name = NOW;

// pretty-prints to stdout
#define FINISH_TIMING_PRINT(name)                                                                                      \
  auto generated_timer_777_elapsed_##name =                                                                            \
      std::chrono::duration_cast<std::chrono::microseconds>(NOW - generated_timer_777_##name);                         \
  std::cout << "--- TIMER RESULT: section " << #name << " took "                                                       \
            << pretty_time(generated_timer_777_elapsed_##name.count()) << std::endl;

// reports as integer wth microseconds
#define FINISH_TIMING(name)                                                                                            \
  (std::chrono::duration_cast<std::chrono::microseconds>(NOW - generated_timer_777_##name).count())
// reports as double with seconds
#define FINISH_TIMING_SEC(name)                                                                                            \
  (((double)std::chrono::duration_cast<std::chrono::microseconds>(NOW - generated_timer_777_##name).count())/(1e6))

inline std::string pretty_time(long long microsec) {
  // Useful constants
  long long MILLIS = 1000;
  long long SECOND = 1000 * MILLIS;
  long long MINUTE = 60 * SECOND;
  long long HOUR = 60 * MINUTE;

  // Greater than 1 hour
  if (microsec > HOUR) {
    long long hours = microsec / HOUR;
    microsec -= hours * HOUR;
    long long minutes = microsec / MINUTE;

    return std::to_string(hours) + " hr, " + std::to_string(minutes) + " min";
  }

  // Greater than 1 minute
  else if (microsec > MINUTE) {
    long long minutes = microsec / MINUTE;
    microsec -= minutes * MINUTE;
    long long seconds = minutes / SECOND;

    return std::to_string(minutes) + " min, " + std::to_string(seconds) + " sec";
  }

  // Greater than 1 second
  else if (microsec > SECOND) {
    double seconds = microsec / (double)SECOND;

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << seconds << " sec";
    return stream.str();
  }

  // Greater than 1 millisecond
  else if (microsec > MILLIS) {
    double millis = microsec / (double)MILLIS;

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << millis << " ms";
    return stream.str();
  }

  // Times less than 1 millisecond
  else {
    double micros = microsec;

    std::stringstream stream;
    // note the nifty unicode \mu.
    // I apologize when this breaks something later.
    stream << std::fixed << std::setprecision(2) << microsec << " µs";
    return stream.str();
  }
}
