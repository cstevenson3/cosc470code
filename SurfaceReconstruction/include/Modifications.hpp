#ifndef SURFACE_RECONSTRUCTION_MODIFICATIONS_HPP
#define SURFACE_RECONSTRUCTION_MODIFICATIONS_HPP

#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include <vector>

#include "Contours.hpp"
#include "PointCorrespondence.hpp"
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
     * NOT TESTED
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
     * Branch point correspondence across two slices by splitting the single contour
     * @param points Coordinates of points
     * @param sourceContourList The source contours for one slice
     * @param neighbourContourList The neighbour contours for the other slice
     * @param forwardCorrespondence Contour correspondence in one direction
     * @param reverseCorrespondence Contour correspondence in the opposite direction
    */
    std::vector<MeshUtil::TriangleIndices> contourSplitting(std::vector<glm::vec3>& points,
                                                            std::vector<Contours::Contour>& sourceContourList,
                                                            std::vector<Contours::Contour>& neighbourContourList,
                                                            std::vector<ContourCorrespondence::CorrespondenceIndices>& forwardCorrespondence, 
                                                            std::vector<ContourCorrespondence::CorrespondenceIndices>& reverseCorrespondence,
                                                            PointCorrespondence::Algorithm pointCorrespondenceMethod);
}  // namespace Modifications.

#endif //SURFACE_RECONSTRUCTION_MODIFICATIONS_HPP