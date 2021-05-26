#ifndef SURFACE_RECONSTRUCTION_CONTOURCORRESPONDENCE_H
#define SURFACE_RECONSTRUCTION_CONTOURCORRESPONDENCE_H


#include <glm/vec3.hpp>
#include <gsl/gsl_util>
#include <utility>
#include <vector>

#include "Contours.hpp"
#include "NotImplemented.hpp"

namespace ContourCorrespondence {
    using Contours::Contour;
    typedef std::pair<std::vector<Contour>, std::vector<Contour>> Correspondence;
    typedef std::pair<uint64_t, std::vector<uint64_t>> CorrespondenceIndices;

    enum class CorrespondenceMethod{
        allToAll,  // Matches all contours on the current slice to all contours on the next slice.
        closestCentroid,  // Match contours to the contour with the nearest centroid on the next slice.
        centroidWithinRadius  // Match contours which have a contour centroid within the radius of the current contour.
    };

    struct Config {
        CorrespondenceMethod method;  // The type of algorithm to use to match contours.
    };

    /**
     * Finds a contour correspondence between two sets of contours. Return indices of contours instead of contours.
     * @param points    The global point set.
     * @return          A contour correspondence.
     */
    std::vector<CorrespondenceIndices> findContourCorrespondenceIndices(const std::vector<glm::vec3>& points,
                                                          const std::vector<Contour>&,
                                                          const std::vector<Contour>&,
                                                          CorrespondenceMethod);

    /**
     * Finds a contour correspondence between two sets of contours.
     * @param points    The global point set.
     * @return          A contour correspondence.
     */
    std::vector<Correspondence> findContourCorrespondence(const std::vector<glm::vec3>& points,
                                                          const std::vector<Contour>&,
                                                          const std::vector<Contour>&,
                                                          CorrespondenceMethod);
}

#endif //SURFACE_RECONSTRUCTION_CONTOURCORRESPONDENCE_H
