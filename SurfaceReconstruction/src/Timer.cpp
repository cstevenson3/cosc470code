#include "Timer.hpp"

using std::cout;
using std::string;

// Starts timing functionality.
void Timer::start() {
    startClock = clock();
    startTime = std::chrono::high_resolution_clock::now();
}

// Stops the timer.
void Timer::stop() {
    elapsedClock = clock() - startClock;
    elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
}

void Timer::printElapsedTime(const string& message) {
    cout << "Time information for task: " << message << '\n';
    printElapsedTime();
}

// Prints time information such as CPU time and real time elapsed.
void Timer::printElapsedTime() {
    // Calculate the real elapsed time in milliseconds.
    auto elapsedTimeMilliseconds = std::chrono::duration<double, std::milli>(elapsedTime).count();

    cout << "\tCPU time elapsed: " << 1000.0 * elapsedClock / CLOCKS_PER_SEC << "ms\n";
    cout << "\tReal time elapsed: " << elapsedTimeMilliseconds << "ms\n\n";
}