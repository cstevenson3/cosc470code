#ifndef SURFACE_RECONSTRUCTION_POINTUTIL_H
#define SURFACE_RECONSTRUCTION_POINTUTIL_H

#include <string>
#include <glm/geometric.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace PointUtil {
    /**
     * Checks whether two points p1 and p2 are within a certain distance of each other.
     * @return  True if the points are within the given threshold of each other. False otherwise.
     */
    bool pointDistanceWithinThreshold2d(glm::vec3 p1, glm::vec3 p2, float);

    double distanceXZ(glm::vec3, glm::vec3);
    std::string pointAsString(glm::vec3);
}  // namespace PointUtil.


#endif //SURFACE_RECONSTRUCTION_POINTUTIL_H
