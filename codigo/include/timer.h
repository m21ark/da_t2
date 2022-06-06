#ifndef DA_T2_TIMER_H
#define DA_T2_TIMER_H

#include <chrono>

using namespace std::chrono;
using namespace std;

typedef high_resolution_clock::time_point time_point_t;

/**
 * Timer class that stores current time at command.
 * Useful for measuring time deltas in code
 */
class [[maybe_unused]] Timer {
private:
    /**
     * Start and End time deltas variables
     */
    static time_point_t start_time, stop_time;
public:

    /**
     * Sets start_time static var to the current time at the calling moment
     */
    [[maybe_unused]] static void start();

    /**
     * Sets stop_time static var to the current time at the calling moment
     */
    [[maybe_unused]] static void stop();

    /**
     * Returns the current time delta between the calling moment and the
     * time saved at start_time var
     * @return time since last start() call: current_time - start_time
     */
    [[maybe_unused]] static float getCurrentTime();

    /**
     * Returns the time delta between the calling of start() and stop()
     * @return time delta: stop_time - start_time
     */
    [[maybe_unused]] static float getTime();
};

#endif //DA_T2_TIMER_H
