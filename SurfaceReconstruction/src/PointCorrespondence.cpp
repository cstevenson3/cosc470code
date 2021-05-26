#include "PointCorrespondence.hpp"

namespace PointCorrespondence {
    using std::vector;
    using std::pair;
    using MeshUtil::Correspondence;

    namespace {

        /**
         * Returns the contour index (not global) for the closest point in the contour.
         * @param point
         * @param points
         * @param neighbour
         * @return
         */
        uint64_t getClosestPointIndex(const glm::vec3 point, const vector<glm::vec3>& points, const Contour& neighbour)
        {
            auto closestDistance = std::numeric_limits<float>::infinity();
            uint64_t closest = 0;
            for (uint64_t i = 0; i < neighbour.size(); i++) {
                auto distance = glm::distance(point, points[neighbour[i]]);
                if (distance < closestDistance) {
                    closestDistance = distance;
                    closest = i;
                }
            }
            return closest;
        }

        Correspondence shortestEuclideanDistance(const vector<glm::vec3>& points, const Contour& source, const Contour& neighbour)
        {
            Correspondence correspondence;
            uint64_t previous = 0;
            for (auto sourcePointIndex: source) {
                auto closest = getClosestPointIndex(points[sourcePointIndex], points, neighbour);
                while (previous < closest) {
                    previous++;
                    auto correspondingPair = std::make_pair(sourcePointIndex, neighbour[previous]);
                    correspondence.emplace_back(correspondingPair);
                }

                previous = closest;

                auto correspondingPair = std::make_pair(sourcePointIndex, neighbour[closest]);
                correspondence.emplace_back(correspondingPair);
            }

            return correspondence;
        }

        TriangleIndices getPatchTriangle(Correspondence correspondence, uint64_t mergedPoint)
        {
            vector<uint64_t> toPatchFirst;

            for (auto pointPair : correspondence) {
                auto currentSource = pointPair.first;
                auto currentNeighbour = pointPair.second;
                if (currentSource == mergedPoint) {
                    toPatchFirst.emplace_back(currentNeighbour);
                }
                if (currentNeighbour == mergedPoint) {
                    toPatchFirst.emplace_back(currentSource);
                }
            }

            if (toPatchFirst.size() < 2) {
                std::cout << "Size: " << toPatchFirst.size();
                std::cout << "Unexpected..\n";
                throw NotImplemented();
            }

            TriangleIndices tri{mergedPoint, toPatchFirst.front(), toPatchFirst.back()};
            return tri;
        }

        TriangleIndices getAltPatchTriangle(Correspondence correspondence, uint64_t mergedPoint) {
            vector<uint64_t> toPatchFirst;

            for (auto pointPair : correspondence) {
                auto currentSource = pointPair.first;
                auto currentNeighbour = pointPair.second;
                if (currentSource == mergedPoint) {
                    toPatchFirst.emplace_back(currentNeighbour);
                }
                if (currentNeighbour == mergedPoint) {
                    toPatchFirst.emplace_back(currentSource);
                }
            }

            if (toPatchFirst.size() < 2) {
                std::cout << "Size: " << toPatchFirst.size();
                std::cout << "Unexpected..\n";
                throw NotImplemented();
            }

            if (toPatchFirst.size() == 2) {
                TriangleIndices tri{mergedPoint, toPatchFirst[1], toPatchFirst[0]};
                return tri;
            }

            for (uint64_t i = 1; i < toPatchFirst.size(); i++){
                if (std::fabs((toPatchFirst[i]) - toPatchFirst[i-1]) > 1) {
                    TriangleIndices tri{mergedPoint, toPatchFirst[i], toPatchFirst[i-1]};
                    return tri;
                }
            }

            throw NotImplemented();
        }
    }  // namespace

    Correspondence getPointCorrespondence(const vector<glm::vec3>& points, const Contour& source, const Contour& neighbour, Algorithm algorithm)
    {
        Correspondence correspondence;
        switch (algorithm) {
            case Algorithm::shortestpath : {
                correspondence = shortestEuclideanDistance(points, source, neighbour);
                break;
            }
            case Algorithm::dynamictimewarping : {
                correspondence = DTW::getCorrespondence(points, source, neighbour, DTW::CostFunction::euclideanDistance);
                break;
            }
            case Algorithm::dynamictimewarpingwindow : {
                correspondence = DTW::getCorrespondenceWarpingWindow(points, source, neighbour, DTW::CostFunction::euclideanDistance, 0.1);
                break;
            }
            case Algorithm::shortestangle: {
                throw NotImplemented();
            }
        }

        return correspondence;
    }

    vector<TriangleIndices> patchTris(Correspondence correspondence, pair<uint64_t, uint64_t> omitIndices)
    {
        vector<TriangleIndices> tris;
        auto firstOmit = omitIndices.first;
        auto secondOmit = omitIndices.second;

        auto tri1 = getPatchTriangle(correspondence, firstOmit);
        auto tri2 = getAltPatchTriangle(correspondence, secondOmit);

        tris.emplace_back(tri1);
        tris.emplace_back(tri2);

        return tris;
    }

    std::vector<TriangleIndices> getEdgeCaseTriangles(const std::vector<glm::vec3>& points,
                                                      const Contour& source,
                                                      const Contour& neighbour,
                                                      std::pair<uint64_t, uint64_t> mergePoints)
    {
        // TODO(recomputing): this is re-computing already computed information. Refactor.
        return DTW::getEdgeCaseTrisWindow(points, source, neighbour, DTW::CostFunction::euclideanDistance, mergePoints, 0.1);
    }

}  // namespace PointCorrespondence.