#ifndef SURFACE_RECONSTRUCTION_POINTCORRESPONDENCE_H
#define SURFACE_RECONSTRUCTION_POINTCORRESPONDENCE_H

#include <cmath>
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>
#include <vector>

#include "DTW.hpp"
#include "Contours.hpp"
#include "MeshUtil.hpp"
#include "NotImplemented.hpp"

namespace PointCorrespondence {
    using Contours::Contour;
    using MeshUtil::TriangleIndices;

    enum class Algorithm{
        shortestpath,
        dynamictimewarping,
        dynamictimewarpingwindow,
        shortestangle
    };


    /**
     * Generate a correspondence between two contours.
     * @param points    The global point set.
     * @param source    The source contour.
     * @param neighbour The neighbouring contour.
     * @return          A correspondence of points.
     */
    MeshUtil::Correspondence getPointCorrespondence(const std::vector<glm::vec3>& points,
                                                                      const Contour& source,
                                                                      const Contour& neighbour,
                                                                      Algorithm algorithm);

    /**
     * Patch missing triangles that are generated in branching.
     * @param correspondence    The point correspondence generated.
     * @param omitIndices       The merging points.
     * @return                  Patch triangles.
     */
    std::vector<TriangleIndices> patchTris(MeshUtil::Correspondence correspondence, std::pair<uint64_t, uint64_t> omitIndices);

    /**
     * Get edge case triangles that are omitted in the case of merged contours. Expects DTW to be used.
     * @param points        The global point set.
     * @param source        The source contour.
     * @param neighbour     The neighbour contour.
     * @param mergePoints   The points which have been merged.
     * @return              A set of triangle indicies.
     */
    std::vector<TriangleIndices> getEdgeCaseTriangles(const std::vector<glm::vec3>& points,
                                                      const Contour& source,
                                                      const Contour& neighbour,
                                                      std::pair<uint64_t, uint64_t> mergePoints);
}  // namespace PointCorrespondence.


#endif //SURFACE_RECONSTRUCTION_POINTCORRESPONDENCE_H
