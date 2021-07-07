#ifndef SURFACE_RECONSTRUCTION_MODIFICATIONS_HPP
#define SURFACE_RECONSTRUCTION_MODIFICATIONS_HPP

#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>

#include "Contours.hpp"
#include "MeshUtil.hpp"

namespace Modifications {
    /**
     * Get correspondence by point angles from centroids around contours.
     * @param points        Reference to global point set.
     * @param source        Source contour.
     * @param neighbour     Neighbour contour.
     * @return              A point correspondence.
    */
    MeshUtil::Correspondence pointCorrespondencePointAngle(const std::vector<glm::vec3>& points,
                                                            const Contours::Contour& source,
                                                            const Contours::Contour& neighbour);

    /**
     * Get point correspondence by aligning contours (position and rotation) before DTW
     * @param points        Reference to global point set.
     * @param source        Source contour.
     * @param neighbour     Neighbour contour.
     * @return              A point correspondence.
    */
    MeshUtil::Correspondence alignedDTW(const std::vector<glm::vec3>& points,
                                        const Contours::Contour& source,
                                        const Contours::Contour& neighbour);
}  // namespace Modifications.

#endif //SURFACE_RECONSTRUCTION_MODIFICATIONS_HPP