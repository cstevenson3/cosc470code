#ifndef SURFACE_RECONSTRUCTION_TIMER_HPP
#define SURFACE_RECONSTRUCTION_TIMER_HPP

#include <ctime>
#include <chrono>
#include <iostream>

class Timer {
public:
    Timer(): startClock(0), elapsedClock(0), startTime(), elapsedTime(){};
    void start();
    void stop();
    void printElapsedTime(const std::string&);
    void printElapsedTime();

private:
    std::clock_t startClock;
    std::clock_t elapsedClock;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::duration<double> elapsedTime;
};


#endif //SURFACE_RECONSTRUCTION_TIMER_HPP
