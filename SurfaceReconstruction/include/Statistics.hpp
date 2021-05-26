#ifndef SURFACE_RECONSTRUCTION_STATISTICS_HPP
#define SURFACE_RECONSTRUCTION_STATISTICS_HPP

#include <iostream>
#include "ContourStatistics.hpp"
#include "NotImplemented.hpp"

class Statistics {
public:
    Statistics(): contourStats() {};

    void logToCSV();
    void printStatistics();

private:
    ContourStatistics contourStats;
};


#endif //SURFACE_RECONSTRUCTION_STATISTICS_HPP
