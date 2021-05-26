#ifndef SURFACE_RECONSTRUCTION_CONTOURSTATISTICS_HPP
#define SURFACE_RECONSTRUCTION_CONTOURSTATISTICS_HPP

#include <iostream>

class ContourStatistics {
public:
    ContourStatistics(): contourLength(0) {};

    void printStatistics();
private:
    int contourLength;
};


#endif //SURFACE_RECONSTRUCTION_CONTOURSTATISTICS_HPP
