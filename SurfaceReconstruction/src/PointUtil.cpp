#include "PointUtil.hpp"

namespace PointUtil {
    bool pointDistanceWithinThreshold2d(glm::vec3 p1, glm::vec3 p2, float threshold)
    {
        auto distance = distanceXZ(p1, p2);
        return distance <= threshold;
    }


    double distanceXZ(glm::vec3 p1, glm::vec3 p2)
    {
        glm::vec2 p1as2d{p1.x, p1.z};
        glm::vec2 p2as2d{p2.x, p2.z};

        return glm::distance(p1as2d, p2as2d);
    }


    std::string pointAsString(glm::vec3 point)
    {
        std::string pointStr;
        pointStr.append("(x, y, z): (");
        pointStr.append(std::to_string(point.x));
        pointStr.append(", ");
        pointStr.append(std::to_string(point.y));
        pointStr.append(", ");
        pointStr.append(std::to_string(point.z));
        pointStr.append(")\n");

        return pointStr;
    }
}  // namespace PointUtil.