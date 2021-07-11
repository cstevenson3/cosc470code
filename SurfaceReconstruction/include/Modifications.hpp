#ifndef SURFACE_RECONSTRUCTION_MODIFICATIONS_HPP
#define SURFACE_RECONSTRUCTION_MODIFICATIONS_HPP

#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include <vector>

#include "Contours.hpp"
#include "ContourCorrespondence.hpp"
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

    /**
     * Branch point correspondence by splitting the single contour
     * @param contourStack Contour stack with points and contours
     * @param forwardCorrespondence Contour correspondence in one direction
     * @param reverseCorrespondence Contour correspondence in the opposite direction
    */
    std::vector<MeshUtil::TriangleIndices> contourSplitting(Contours::Stack& contourStack, 
                                                            std::vector<ContourCorrespondence::CorrespondenceIndices>& forwardCorrespondence, 
                                                            std::vector<ContourCorrespondence::CorrespondenceIndices>& reverseCorrespondence);
}  // namespace Modifications.

#endif //SURFACE_RECONSTRUCTION_MODIFICATIONS_HPP