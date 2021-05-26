#ifndef SURFACE_RECONSTRUCTION_CONTOURS_H
#define SURFACE_RECONSTRUCTION_CONTOURS_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <glm/vec3.hpp>
#include <gsl/gsl_util>

#include "MeshUtil.hpp"
#include "NotImplemented.hpp"
#include "PointUtil.hpp"
#include "ReconstructionConfig.hpp"
#include "ReconstructionErrors.hpp"

namespace Contours {
    typedef std::vector<uint64_t> Contour;
    typedef std::vector<Contour> ContourList;

    enum class MergingStrategy {
        divideAtClosestPoint,
        discardQuarter
    };

    class Stack {
    public:
        std::vector<glm::vec3> points;
        std::vector<ContourList> contours;
        std::string toString();
    };

    namespace Extremities {
        float maxDistanceFromCentroid(const std::vector<glm::vec3>& points, const Contour&);
    }

    std::pair<uint64_t, uint64_t> findOmitIndices(const std::vector<glm::vec3>& points, Contour c1, Contour c2);
    std::pair<uint64_t, uint64_t> findNextIndices(const std::vector<glm::vec3>& points, Contour c1, Contour c2);

    /**
     * Find points on contours c1 and c2 with the lowest x values.
     * @param points    Global point set.
     * @param c1        Source contour.
     * @param c2        Neighbour contour.
     * @return          A pair of indices for points with the lowest x values.
     */
    std::pair<uint64_t, uint64_t> findLowestXIndices(const std::vector<glm::vec3>& points, Contour c1, Contour c2);

    /**
     * Find the closest pair of points in two contours.
     * @param points    Global point set.
     * @param c1        Source contour.
     * @param c2        Neighbour contour.
     * @return          A pair of indices for the closest two points.
     */
    std::pair<uint64_t, uint64_t> findClosestIndices(const std::vector<glm::vec3>& points, Contour c1, Contour c2);

    /**
     * Re-orders contours from a given index.
     * @param contour   The contour to re-order.
     * @param index     The index to re-order from.
     * @return          A re-ordered contour.
     */
    Contour reorderContourFrom(const Contour& contour, uint64_t index);

    /**
     * Find contours within range of a given source contour. Works the same as findContoursWithinRange except returns indices.
     * @param points    The global point set.
     * @param contour   The source contour.
     * @param toMatch   The set of neighbours to search for matches in.
     * @return          A set of indices corresponding to matched neighbours.
     */
    std::vector<uint64_t> findContourIndicesWithinRange(const std::vector<glm::vec3>& points,
                                                   const Contour& contour,
                                                   std::vector<Contour> toMatch);

    std::vector<Contour> findContoursWithinRange(const std::vector<glm::vec3>& points,
            const Contour& contour, std::vector<Contour> toMatch);


    /**
     * Find the closest contour in a set of contours, given an input contour. Uses contour centroid.
     * @param points    The global point set.
     * @return          The closest contour.
     */
    Contour findClosestContour(const std::vector<glm::vec3>& points, Contour, std::vector<Contour>);

    /**
     * Compute contour centroid.
     * @param points    Global point set.
     * @return          The contour centroid.
     */
    glm::vec3 computeCentroid(const std::vector<glm::vec3>& points, Contour);

    /**
     * Load from a format used for real data.
     * @return  A loaded contour stack.
     */
    Stack loadRealFormatted(ReconstructionConfig::Configuration);

    /**
     * Load from modified real data format. -1 denotes end of contours.
     * @return  Loaded contour stack.
     */
    Stack loadRealNewFormat(ReconstructionConfig::Configuration);

    /**
     * Load contours from file which are separated by whitespace.
     * @param filename  Filename to load contours from.
     * @return          A loaded contour stack.
     */
    Stack loadWhitepaceFormatted(const std::string& filename);

    /**
     * Load from modified real data format.
     * First line is the number of contours. Following lines are x, y values.
     * @return  Loaded contour stack.
     */
    Stack loadAltTestFormat(ReconstructionConfig::Configuration);

    /**
     * Merges two contours into one based on their closest points.
     * @return  A single merged contour.
     */
    Contour mergeContours(const std::vector<glm::vec3>&, const Contour&, const Contour&);
}  // namespace Contours.


#endif //SURFACE_RECONSTRUCTION_CONTOURS_H
