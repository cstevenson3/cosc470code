#ifndef SURFACE_RECONSTRUCTION_CONTOURDATA_HPP
#define SURFACE_RECONSTRUCTION_CONTOURDATA_HPP

#include <string>
#include <iostream>

namespace ReconstructionConfig {
    struct ContourConfig {
        unsigned int minSize;   // Minimum contour size.
        unsigned int maxSize;   // Maximum contour size.
        double scaling;         // Scaling factor between points.
    };


    struct SliceConfig {
        unsigned int min;       // Minimum slice index.
        unsigned int max;       // Maximum slice index.
        double height;          // Distance between slices.
    };

    enum class DataFormat {
        whiteSpaceFormatted,
        realContourFormatted,   // mukundan format.
        realNewFormat,          // Altered mukundan format (-1 terminates the sequence of contours).
        altTestFormat           // Another alternative testing format. numpoints, followed by contour xy co-ords.
    };


    struct Configuration {
        ContourConfig contour;
        SliceConfig slices;
        std::string filePrefix; // Input file name prefix.
        DataFormat dataFormat;
    };


    Configuration configurecli();

    DataFormat inputDataFormat();
    std::string inputFilenamePrefix();
    unsigned int inputMinContourSize();
    unsigned int inputMaxContourSize();
    unsigned int inputMinSlices();
    unsigned int inputMaxSlices();
}


#endif
