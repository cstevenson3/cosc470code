#ifndef SURFACE_RECONSTRUCTION_DTW_H
#define SURFACE_RECONSTRUCTION_DTW_H

#include <glm/geometric.hpp>

#include "Contours.hpp"
#include "MeshUtil.hpp"

namespace DTW {
    enum class CostFunction {
        euclideanDistance,
        euclidSizeWeighted,
        triangleArea
    };

    class DTWTable {
    public:
        void compute(const std::vector<glm::vec3>& points,
                     Contours::Contour source,
                     Contours::Contour neighbour,
                     CostFunction costFunction);

        /**
         * Get the dtw warping path. Doesn't use any global constraints.
         * @return  The warping path for the currently stored dtw table.
         */
        std::vector<std::pair<uint64_t, uint64_t>> getWarpingPath();

        /**
         * Get the dynamic time warping path. Uses a given global warping window constraint.
         * Uses the sakoe-chiba band.
         * Assumes the dtwtable has already been computed.
         * @param window    The global warping window constraint.
         * @return          The warping path for the currently stored dtwtable.
         */
        std::vector<std::pair<uint64_t, uint64_t>> getWarpingPathWindow(double window);

        /**
         * Helper function for printing the current dtw table.
         */
        void printTable();
    private:
        void initTable(uint64_t numRows, uint64_t numColumns);
        float computeCellValue(float, float, float, float);
        double getPrevCellValWithArea(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float cost);
        std::vector<std::vector<float>> table;
    };

    /**
     * Get correspondence using dynamic time warping.
     * @param points        Reference to global point set.
     * @param source        Source contour.
     * @param neighbour     Neighbour contour.
     * @param costFunction  Cost function to use when creating table.
     * @return              A point correspondence.
     */
    MeshUtil::Correspondence getCorrespondence(const std::vector<glm::vec3>& points,
                                               const Contours::Contour& source,
                                               const Contours::Contour& neighbour,
                                               CostFunction costFunction);

    /**
     * Get correspondence using dynamic time warping.
     * Uses a global warping window constraint.
     * @param points                    The global point set.
     * @param source                    The source contour.
     * @param neighbour                 Neighbouring contour.
     * @param costFunction              The type of cost function to use.
     * @param warpingWindowConstraint   The global warping window constraint.
     * @return                          A correspondence between two series of points (source and neighbour).
     */
    MeshUtil::Correspondence getCorrespondenceWarpingWindow(const std::vector<glm::vec3>& points,
                                                            const Contours::Contour& source,
                                                            const Contours::Contour& neighbour,
                                                            CostFunction costFunction,
                                                            double warpingWindowConstraint);

    /**
     * Get edge case triangles for branching contours.
     * @param points        Global point set.
     * @param source        Source contour.
     * @param neighbour     Neighbour contour.
     * @param costFunction  Cost function to use when creating table.
     * @param mergePoints
     * @return
     */
    std::vector<MeshUtil::TriangleIndices> getEdgeCaseTris(const std::vector<glm::vec3>& points,
                                                           const Contours::Contour& source,
                                                           const Contours::Contour& neighbour,
                                                           CostFunction costFunction,
                                                           std::pair<uint64_t, uint64_t> mergePoints);

    /**
     *
     * @param points
     * @param source
     * @param neighbour
     * @param costFunction
     * @param mergePoints
     * @param warpingWindow
     * @return
     */
    std::vector<MeshUtil::TriangleIndices> getEdgeCaseTrisWindow(const std::vector<glm::vec3>& points,
                                                            const Contours::Contour& source,
                                                            const Contours::Contour& neighbour,
                                                            CostFunction costFunction,
                                                            std::pair<uint64_t, uint64_t> mergePoints,
                                                            double warpingWindow);
}  // namespace DTW.


#endif //SURFACE_RECONSTRUCTION_DTW_H
