#ifndef SURFACE_RECONSTRUCTION_RECONSTRUCTIONERRORS_H
#define SURFACE_RECONSTRUCTION_RECONSTRUCTIONERRORS_H

#include <stdexcept>

namespace ReconstructionErrors {
    class PointParsingError: public std::logic_error {
    public:
        PointParsingError() : std::logic_error("Unable to parse points from file.") { };
    };

    class ContourProcessingError: public std::logic_error {
    public:
        ContourProcessingError() : std::logic_error("Unexpected end of contour file.") {};
    };
}


#endif //SURFACE_RECONSTRUCTION_RECONSTRUCTIONERRORS_H
