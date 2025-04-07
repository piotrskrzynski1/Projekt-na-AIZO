#include "Timer.h"

Timer::Timer() : running(false) {}

void Timer::reset() {
    running = false;
}

int Timer::start() {
    if (!running) {
        start_time = Clock::now();
        running = true;
    }
    return 0;
}

int Timer::stop() {
    if (running) {
        end_time = Clock::now();
        running = false;
    }
    return 0;
}

long long Timer::result() const {
    if (!running) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    }
    return -1; // Timer nie był zatrzymany
}
