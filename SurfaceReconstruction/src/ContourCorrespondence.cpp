#include "ContourCorrespondence.hpp"

namespace ContourCorrespondence {
    using std::vector;
    using std::pair;

    namespace{
        vector<Correspondence> allToAll(vector<Contour> sourceContours, vector<Contour> neighbours)
        {
            vector<Correspondence> correspondenceList;
            for (auto& source: sourceContours) {
                vector<Contour> matchedSources;
                vector<Contour> matchedNeighbours;
                // Pre-allocate.
                matchedNeighbours.reserve(neighbours.size());
                for (auto& neighbour: neighbours) {
                    matchedNeighbours.emplace_back(neighbour);
                }
                matchedSources.emplace_back(source);
                Correspondence correspondence;
                correspondence = std::make_pair(matchedSources, matchedNeighbours);
                correspondenceList.emplace_back(correspondence);
            }
            return correspondenceList;
        }

        vector<Correspondence> closestCentroid(const vector<glm::vec3>& points, vector<Contour> sourceContours,
                                               const vector<Contour>& neighbours)
        {
            vector<Correspondence> correspondenceList;
            for (auto& source: sourceContours) {
                vector<Contour> matchedSources;
                vector<Contour> matchedNeighbours;

                if (!neighbours.empty()) {
                    matchedNeighbours.emplace_back(Contours::findClosestContour(points, source, neighbours));
                }

                matchedSources.emplace_back(source);
                Correspondence correspondence;
                correspondence = std::make_pair(matchedSources, matchedNeighbours);
                correspondenceList.emplace_back(correspondence);
            }

            return correspondenceList;
        }

        vector<Correspondence> distanceToCentroid(const vector<glm::vec3>& points, vector<Contour> sourceContours,
                                                  const vector<Contour>& neighbours)
        {
            vector<Correspondence> correspondenceList;

            for (auto& source: sourceContours) {
                vector<Contour> matchedSources;
                vector<Contour> matchedNeighbours;

                matchedSources.emplace_back(source);
                if (!neighbours.empty()) {
                    matchedNeighbours = Contours::findContoursWithinRange(points, source, neighbours);
                }

                Correspondence correspondence;
                correspondence = std::make_pair(matchedSources, matchedNeighbours);
                correspondenceList.emplace_back(correspondence);
            }

            return correspondenceList;
        }

        vector<CorrespondenceIndices> distanceToCentroidIndices(const vector<glm::vec3>& points,
                const vector<Contour>& sourceContours,
                const vector<Contour>& neighbours)
        {
            vector<CorrespondenceIndices> correspondenceList;

            for (uint64_t cindex = 0; cindex < sourceContours.size(); cindex++) {
                pair<uint64_t, vector<uint64_t>> matching;
                vector<uint64_t> matchedNeighbours;

                if (!neighbours.empty()) {
                    matchedNeighbours = Contours::findContourIndicesWithinRange(points, sourceContours[cindex], neighbours);
                }

                CorrespondenceIndices correspondence;
                correspondence = std::make_pair(cindex, matchedNeighbours);
                correspondenceList.emplace_back(correspondence);
            }

            return correspondenceList;
        }
    }  // namespace.


    vector<CorrespondenceIndices> findContourCorrespondenceIndices(const vector<glm::vec3>& points,
            const vector<Contour>& sources,
            const vector<Contour>& neighbours,
            CorrespondenceMethod method)
    {
        vector<CorrespondenceIndices> correspondence;
        switch (method) {
            case CorrespondenceMethod::centroidWithinRadius : {
                correspondence = distanceToCentroidIndices(points, sources, neighbours);
                break;
            }
            case CorrespondenceMethod::closestCentroid : {
                throw NotImplemented();
            }
            case CorrespondenceMethod::allToAll : {
                throw NotImplemented();
            }
        }

        return correspondence;
    }


    vector<Correspondence> findContourCorrespondence(const vector<glm::vec3>& points, const vector<Contour>& sources,
                                         const vector<Contour>& neighbours,
                                         CorrespondenceMethod method)
    {
        vector<Correspondence> correspondence;
        switch (method) {
            case CorrespondenceMethod::allToAll : {
                correspondence = allToAll(sources, neighbours);
                break;
            }
            case CorrespondenceMethod::closestCentroid : {
                correspondence = closestCentroid(points, sources, neighbours);
                break;
            }
            case CorrespondenceMethod::centroidWithinRadius: {
                correspondence = distanceToCentroid(points, sources, neighbours);
                break;
            }
        }

        return correspondence;
    }
}  // namespace ContourCorrespondence.
