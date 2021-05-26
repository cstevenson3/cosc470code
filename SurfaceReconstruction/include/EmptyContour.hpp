#ifndef SURFACE_RECONSTRUCTION_EMPTYCONTOUR_HPP
#define SURFACE_RECONSTRUCTION_EMPTYCONTOUR_HPP

#include <stdexcept>

class EmptyContour: public std::logic_error {
public:
    EmptyContour() : std::logic_error("Attempted to make use of an empty contour.") { };
};

#endif //SURFACE_RECONSTRUCTION_EMPTYCONTOUR_HPP
