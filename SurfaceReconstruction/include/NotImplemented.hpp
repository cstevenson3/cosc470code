#ifndef SURFACE_RECONSTRUCTION_NOTIMPLEMENTEDEXCEPTION_HPP
#define SURFACE_RECONSTRUCTION_NOTIMPLEMENTEDEXCEPTION_HPP

#include <stdexcept>

class NotImplemented: public std::logic_error {
public:
    NotImplemented() : std::logic_error("Function not yet implemented.") { };
};


#endif //SURFACE_RECONSTRUCTION_NOTIMPLEMENTEDEXCEPTION_HPP
