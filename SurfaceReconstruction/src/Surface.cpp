#include "Surface.hpp"

#include "Modifications.hpp"

namespace Surface {
    using std::vector;
    using std::string;

    namespace {
        vector<MeshUtil::TriangleIndices> get1To2Branching(vector<glm::vec3>& points,
                PointCorrespondence::Algorithm pointCorrespondenceMethod,
                Contours::Contour source,
                vector<Contours::Contour> neighbours)
        {
            vector<MeshUtil::TriangleIndices> triangles;

            auto omitIndices = Contours::findOmitIndices(points,
                                                         neighbours[0],
                                                         neighbours[1]);
            auto mergedNeighbour = Contours::mergeContours(points,
                                                           neighbours[0],
                                                           neighbours[1]);

            auto pointCorrespondence = PointCorrespondence::getPointCorrespondence(points, source,
                                                                                   mergedNeighbour,
                                                                                   pointCorrespondenceMethod);
            auto newTriangles = MeshUtil::triangulate(pointCorrespondence, omitIndices);

            auto edgeCaseTris = PointCorrespondence::patchTris(pointCorrespondence, omitIndices);
            for (auto triangle : edgeCaseTris) {
                std::cout << triangle.p1 << ", " << triangle.p2 << ", " << triangle.p3 << '\n';
            }

            triangles.insert(triangles.end(), newTriangles.begin(), newTriangles.end());
            triangles.insert(triangles.end(), edgeCaseTris.begin(), edgeCaseTris.end());

            return triangles;
        }
    }  // namespace.

    void Reconstruction::reconstructTwoWay(ContourCorrespondence::CorrespondenceMethod correspondenceMethod,
            PointCorrespondence::Algorithm pointCorrespondenceMethod,
            const string& exportFilename)
    {
        auto reconstructionConfig = ReconstructionConfig::configurecli();
        loadContourStack(reconstructionConfig);
        vector<MeshUtil::TriangleIndices> triangles;

        for (uint64_t i = 0; i < contourStack.contours.size() - 1; i++) {
            auto sourceContourList = contourStack.contours[i];
            auto neighbourContourList = contourStack.contours[i+1];

            auto contourCorrespondence = ContourCorrespondence::findContourCorrespondenceIndices(contourStack.points,
                                                                                          sourceContourList, neighbourContourList, correspondenceMethod);

            auto reverseCorrespondence = ContourCorrespondence::findContourCorrespondenceIndices(contourStack.points,
                                                                                          neighbourContourList, sourceContourList, correspondenceMethod);

            Modifications::contourSplitting(contourStack.points, 
                                            sourceContourList, 
                                            neighbourContourList, 
                                            contourCorrespondence, 
                                            reverseCorrespondence, 
                                            pointCorrespondenceMethod);

            for (auto correspondence : contourCorrespondence) {
                if (correspondence.second.empty()) {
                    std::cout << "There is an unmatched contour.\n";
                } else if (correspondence.second.size() == 1) {
                    if (reverseCorrespondence[correspondence.second[0]].second.size() > 1) {
                        // Check whether this is the first time we have found this reverse branch. Only process it if so.
                        if (correspondence.first == reverseCorrespondence[correspondence.second[0]].second[0]) {
                            std::cout << "2-1 branching case detected\n";
                            vector<Contours::Contour> neighbours;
                            // Convoluted but this adds source contours to neighbours. Have to swap.
                            neighbours.emplace_back(sourceContourList[reverseCorrespondence[correspondence.second[0]].second[0]]);
                            neighbours.emplace_back(sourceContourList[reverseCorrespondence[correspondence.second[0]].second[1]]);
                            auto newTriangles = get1To2Branching(contourStack.points,
                                    pointCorrespondenceMethod,
                                    neighbourContourList[correspondence.second[0]],
                                    neighbours);

                            auto reversedOrder = MeshUtil::reverseTriangleOrder(newTriangles);
                            triangles.insert(triangles.end(), reversedOrder.begin(), reversedOrder.end());
                        }
                    } else {
                        // 1 to 1 case.
                        std::cout << "Non-branching case detected." << std::endl;

                        auto sourceIndex = correspondence.first;
                        auto neighbourIndex = correspondence.second[0];
                        auto source = sourceContourList[sourceIndex];
                        auto neighbour = neighbourContourList[neighbourIndex];
                        auto pointCorrespondence = PointCorrespondence::getPointCorrespondence(contourStack.points,
                                                                                               source, neighbour,
                                                                                               pointCorrespondenceMethod);
                        auto newTriangles = MeshUtil::triangulate(pointCorrespondence);
                        triangles.insert(triangles.end(), newTriangles.begin(), newTriangles.end());
                    }
                } else if (correspondence.second.size() == 2) {
                    std::cout << "1-2 Branching case detected." << std::endl;
                    auto omitIndices = Contours::findOmitIndices(contourStack.points,
                            neighbourContourList[correspondence.second[0]],
                            neighbourContourList[correspondence.second[1]]);
                    //auto nextIndices = Contours::findNextIndices(contourStack.points, correspondence.second[0],
                    //                                            correspondence.second[1]);
                    auto mergedNeighbour = Contours::mergeContours(contourStack.points,
                            neighbourContourList[correspondence.second[0]],
                            neighbourContourList[correspondence.second[1]]);

                    auto source = sourceContourList[correspondence.first];
                    auto pointCorrespondence = PointCorrespondence::getPointCorrespondence(contourStack.points, source,
                                                                                           mergedNeighbour,
                                                                                           pointCorrespondenceMethod);
                    auto newTriangles = MeshUtil::triangulate(pointCorrespondence, omitIndices);

                    auto edgeCaseTris = PointCorrespondence::patchTris(pointCorrespondence, omitIndices);
                    for (auto triangle : edgeCaseTris) {
                        std::cout << triangle.p1 << ", " << triangle.p2 << ", " << triangle.p3 << '\n';
                    }

                    triangles.insert(triangles.end(), newTriangles.begin(), newTriangles.end());
                    triangles.insert(triangles.end(), edgeCaseTris.begin(), edgeCaseTris.end());
                } else {
                    std::cout << "Unhandled case detected." << std::endl;
                }
            }
        }

        MeshUtil::exportToPly(contourStack.points, triangles, exportFilename);
    }

    void Reconstruction::reconstruct(ContourCorrespondence::CorrespondenceMethod correspondenceMethod,
                     PointCorrespondence::Algorithm pointCorrespondenceMethod,
                     const string& exportFilename)
    {
        auto reconstructionConfig = ReconstructionConfig::configurecli();
        loadContourStack(reconstructionConfig);
        vector<MeshUtil::TriangleIndices> triangles;

        for (uint64_t i = 0; i < contourStack.contours.size() - 1; i++) {
            auto sourceContourList = contourStack.contours[i];
            auto neighbourContourList = contourStack.contours[i+1];

            auto contourCorrespondence = ContourCorrespondence::findContourCorrespondence(contourStack.points,
                    sourceContourList, neighbourContourList, correspondenceMethod);

            auto reverseCorrespondence = ContourCorrespondence::findContourCorrespondence(contourStack.points,
                    neighbourContourList, sourceContourList, correspondenceMethod);

            for (auto correspondence : contourCorrespondence) {
                if (correspondence.first.empty() && correspondence.second.empty()) {
                    std::cout << "Both contours in matching are empty.\n";
                } else if (correspondence.first.empty() || correspondence.second.empty()) {
                    std::cout << "There is an unmatched contour.\n";
                } else if (correspondence.first.size() == 1 && correspondence.second.size() == 1) {
                    // 1 to 1 case.
                    std::cout << "Non-branching case detected." << std::endl;

                    auto source = correspondence.first[0];
                    auto neighbour= correspondence.second[0];
                    auto pointCorrespondence = PointCorrespondence::getPointCorrespondence(contourStack.points, source, neighbour, pointCorrespondenceMethod);
                    auto newTriangles = MeshUtil::triangulate(pointCorrespondence);
                    triangles.insert(triangles.end(), newTriangles.begin(), newTriangles.end());
                } else if (correspondence.first.size() == 1 && correspondence.second.size() == 2) {
                    std::cout << "1-2 Branching case detected." << std::endl;

                    auto omitIndices = Contours::findOmitIndices(contourStack.points, correspondence.second[0],
                                                                 correspondence.second[1]);
                    //auto nextIndices = Contours::findNextIndices(contourStack.points, correspondence.second[0],
                     //                                            correspondence.second[1]);
                    auto mergedNeighbour = Contours::mergeContours(contourStack.points,
                            correspondence.second[0], correspondence.second[1]);

                    // TODO(duplicated-triangulation-code): This is the same as in the 1-1 case. Refactor.
                    auto source = correspondence.first[0];
                    auto pointCorrespondence = PointCorrespondence::getPointCorrespondence(contourStack.points, source, mergedNeighbour, pointCorrespondenceMethod);
                    auto newTriangles = MeshUtil::triangulate(pointCorrespondence, omitIndices);

                    auto edgeCaseTriangles = PointCorrespondence::getEdgeCaseTriangles(contourStack.points, source, mergedNeighbour, omitIndices);

                    //auto edgeCaseIndices = MeshUtil::triangulateEdgeCase(pointCorrespondence, omitIndices, nextIndices);

                    for (auto triangle : edgeCaseTriangles){
                        std::cout << triangle.p1 << ", " << triangle.p2 << ", " << triangle.p3 << '\n';
                    }

                    triangles.insert(triangles.end(), newTriangles.begin(), newTriangles.end());
                    triangles.insert(triangles.end(), edgeCaseTriangles.begin(), edgeCaseTriangles.end());
                } else if (correspondence.first.size() == 2 && correspondence.second.size() == 1) {
                    std::cout << "2-1 Branching case detected." << std::endl;
                } else {
                    std::cout << "Contour correspondence reports many-to-many. Ignoring." << std::endl;
                }
            }
        }

        MeshUtil::exportToPly(contourStack.points, triangles, exportFilename);
    }

    void Reconstruction::loadContourStack(ReconstructionConfig::Configuration config)
    {
        switch (config.dataFormat) {
            case ReconstructionConfig::DataFormat::whiteSpaceFormatted : contourStack = Contours::loadWhitepaceFormatted(config.filePrefix);
                break;
            case ReconstructionConfig::DataFormat::realContourFormatted : contourStack = Contours::loadRealFormatted(config);
                break;
            case ReconstructionConfig::DataFormat::realNewFormat : contourStack = Contours::loadRealNewFormat(config);
                break;
            case ReconstructionConfig::DataFormat::altTestFormat : contourStack = Contours::loadAltTestFormat(config);
        }
    }
}  // namespace Surface.