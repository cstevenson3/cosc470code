#include "DTW.hpp"

namespace DTW {
    using std::vector;
    using std::pair;

    namespace {

        vector<MeshUtil::TriangleIndices> getEdgeCaseFromWarping(const Contours::Contour& source,
                                                         const Contours::Contour& neighbour,
                                                         vector<pair<uint64_t, uint64_t>> warping,
                                                         pair<uint64_t, uint64_t> mergeIndices)
        {
            vector<MeshUtil::TriangleIndices> tris;
            for (auto step: warping) {
                if (neighbour[step.second] == mergeIndices.first) {
                    uint64_t otherVertex = source[step.first];
                    MeshUtil::TriangleIndices tri{mergeIndices.first, mergeIndices.second, otherVertex};
                    tris.emplace_back(tri);
                    break;
                }
            }

            for (auto step: warping) {
                if (neighbour[step.second] == mergeIndices.second) {
                    uint64_t otherVertex = source[step.first];
                    MeshUtil::TriangleIndices tri{mergeIndices.second, mergeIndices.first, otherVertex};
                    tris.emplace_back(tri);
                    break;
                }
            }

            return tris;
        }

        /**
         * Helper function that returns whether a cell is within a given warping window constraint.
         * Uses the Sakoe-Chiba band.
         * @param tableRatio    The ratio of rows to columns in the table.
         * @param warpingWindow The warping window constraint.
         * @return              True if the cell is within the warping window constraint. False otherwise.
         */
        bool checkWithinWindow(double warpingWindow, uint64_t numRows, uint64_t numColumns, int row, int col)
        {
            double rowWindow = warpingWindow * static_cast<double>(numRows);
            double colWindow = warpingWindow * static_cast<double>(numColumns);

            return ((row - col) < rowWindow) &&
                   ((col - row) < colWindow);
        }

        // Calculate the area of a triangle using Heron's Formula.
        double getTriangleArea(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
        {
            auto a = glm::distance(p1, p2);
            auto b = glm::distance(p2, p3);
            auto c = glm::distance(p3, p1);

            double semiPerimeter = (a + b + c) / 2.0;

            // Heron's formula.
            double area = sqrt(semiPerimeter * (semiPerimeter - a) * (semiPerimeter - b) * (semiPerimeter - c));
            return area;

        }
    }  // namespace.

    vector<pair<uint64_t, uint64_t>> DTWTable::getWarpingPath()
    {
        vector<pair<uint64_t, uint64_t>> warpingPath;

        unsigned int i = 0;
        unsigned int j = 0;
        while (i < (table.size()-1) && j < (table[0].size()-1)) {
            pair<uint64_t, uint64_t> currentCell = std::make_pair(i, j);
            warpingPath.emplace_back(currentCell);
            double below = table[i+1][j];
            double right = table[i][j+1];
            double diagonal = table[i+1][j+1];

            if (diagonal < right) {
                if (diagonal < below) {
                    i += 1;
                    j += 1;
                } else {
                    i += 1;
                }
            } else {
            if (right < below) {
                j += 1;
            } else {
                i += 1;
            }
            }
        }

        while (i < (table.size()-1)) {
            pair<uint64_t, uint64_t> currentCell = std::make_pair(i, j - 1);
            warpingPath.emplace_back(currentCell);
            i += 1;
        }

        while (j < (table[0].size()-1)) {
            pair<uint64_t, uint64_t> currentCell = std::make_pair(i - 1, j);
            warpingPath.emplace_back(currentCell);
            j += 1;
        }

            // Add this at the end for the end of the contour.
        warpingPath.emplace_back(std::make_pair(table.size()-2, 1));

        return warpingPath;
    }

    vector<pair<uint64_t, uint64_t>> DTWTable::getWarpingPathWindow(double window)
    {
        vector<pair<uint64_t, uint64_t>> warpingPath;
        window = 1.0;  // Warping window is currently hard coded.
        unsigned int i = 0;
        unsigned int j = 0;
        while (i < (table.size()-1) && j < (table.front().size()-1)) {
            pair<uint64_t, uint64_t> currentCell = std::make_pair(i, j);
            warpingPath.emplace_back(currentCell);
            double below = table[i+1][j];
            double right = table[i][j+1];
            double diagonal = table[i+1][j+1];

            bool belowValid = checkWithinWindow(window, table.size(), table[0].size(), i+1, j);
            bool rightValid = checkWithinWindow(window, table.size(), table[0].size(), i, j+1);
            bool diagonalValid = checkWithinWindow(window, table.size(), table[0].size(), i+1, j+1);

            if (diagonalValid && diagonal < right && diagonal < below) {
                // Move diagonally.
                i += 1;
                j += 1;
            } else if (rightValid && right < below) {
                // Move right.
                j += 1;
            } else if (belowValid) {
                // Move below.
                i += 1;
            } else if (diagonalValid || rightValid) {
                if (!diagonalValid) {
                    // Move right.
                    j += 1;
                } else if (!rightValid) {
                    // Move diagonal.
                    i += 1;
                    j += 1;
                } else if (diagonal < right) {
                    // Move diagonal.
                    i += 1;
                    j += 1;
                } else {
                    // Move right.
                    j += 1;
                }
            } else {
                std::cout << "Nowhere to move.. Maybe the warping window constraint is too low.\n";
                std::cout << "Below: " << belowValid << "\n";
                std::cout << "Right: " << rightValid << "\n";
                std::cout << "Diagonal: " << diagonalValid << "\n";
                throw NotImplemented();
            }
        }

        while (i < (table.size()-1)) {
            pair<uint64_t, uint64_t> currentCell = std::make_pair(i, j - 1);
            warpingPath.emplace_back(currentCell);
            i += 1;
        }

        while (j < (table[0].size()-1)) {
            pair<uint64_t, uint64_t> currentCell = std::make_pair(i - 1, j);
            warpingPath.emplace_back(currentCell);
            j += 1;
        }

        // Add this at the end for the end of the contour.
        warpingPath.emplace_back(std::make_pair(table.size()-2, 1));

        return warpingPath;
    }

    void DTWTable::compute(const std::vector<glm::vec3> &points, Contours::Contour source, Contours::Contour neighbour,
                           DTW::CostFunction costFunction)
    {
        initTable(source.size()+1, neighbour.size()+1);

        switch (costFunction) {
            case (CostFunction::euclideanDistance) : {
                uint64_t u = 1;
                for (auto i : source) {
                    uint64_t v = 1;
                    for (auto j : neighbour) {
                        float cost = glm::distance(points[i], points[j]);
                        table[u][v] = computeCellValue(cost, table[u-1][v], table[u][v-1], table[u-1][v-1]);
                        v += 1;
                    }
                    u += 1;
                }
                break;
            }
            case (CostFunction::euclidSizeWeighted) : {
                // WIP: Unimplemented.
                auto contourSizeRatio = static_cast<float>(source.size()) / static_cast<float>(neighbour.size());
                auto inverseSizeRatio = 1 / contourSizeRatio;
                uint64_t u = 1;
                for (auto i : source) {
                    uint64_t v = 1;
                    for (auto j : neighbour) {
                        float cost = glm::distance(points[i], points[j]);
                        table[u][v] = computeCellValue(cost, inverseSizeRatio * table[u-1][v],
                                contourSizeRatio * table[u][v-1], table[u-1][v-1]);
                        v += 1;
                    }
                }
                break;
            }

            case (CostFunction::triangleArea) : {
                // WIP: Unimplemented.
                uint64_t u = 1;
                for (uint64_t i = 0; i < source.size(); i++) {
                    uint64_t v = 1;
                    for (uint64_t j = 0; j < neighbour.size(); j++) {
                        if (u > 1) {
                            if (v == 1) {
                                // First column. Check values above only.
                                auto p1 = points[source[i]];
                                auto p2 = points[source[i-1]];
                                auto p3 = points[neighbour[j]];
                                auto above = getPrevCellValWithArea(p1, p2, p3, table[u-1][v]);
                                table[u][v] = static_cast<float>(above);
                            } else {
                                auto p1 = points[source[i]];
                                auto p2 = points[source[i-1]];
                                auto p3 = points[neighbour[j]];
                                auto p4 = points[neighbour[j-1]];

                                auto above = getPrevCellValWithArea(p1, p2, p3, table[u-1][v]);
                                auto left = getPrevCellValWithArea(p1, p3, p4, table[u][v-1]);
                                // Omit the diagonal for now.
                                if (above < left) {
                                    table[u][v] = static_cast<float>(above);
                                } else {
                                    table[u][v] = static_cast<float>(left);
                                }
                            }
                        } else {
                            // First row.
                            if (v == 1) {
                                // First element. Single edge has no area.
                                table[u][v] = 0.0;  // first edge has no area. Initial condition.
                            } else {
                                // Check values to the left only.
                                auto p1 = points[source[i]];
                                auto p3 = points[neighbour[j]];
                                auto p4 = points[neighbour[j-1]];
                                auto left = getPrevCellValWithArea(p1, p3, p4, table[u][v-1]);
                                table[u][v] = static_cast<float>(left);
                            }
                        }
                        v += 1;
                    }
                    u += 1;
                }
                break;
            }
        }
    }

    float DTWTable::computeCellValue(float cost, float n1, float n2, float n3)
    {
        return cost + std::min(n1, std::min(n2, n3));
    }

    double DTWTable::getPrevCellValWithArea(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float cost)
    {
        return getTriangleArea(p1, p2, p3) + cost;
    }

    void DTWTable::initTable(uint64_t numRows, uint64_t numColumns)
    {
        table.clear();
        for (uint64_t i = 0; i < numRows; i++) {
            vector<float> row;
            row.reserve(numColumns);
            for (uint64_t j = 0; j < numColumns; j++) {
                row.emplace_back(std::numeric_limits<float>::infinity());
            }
            table.emplace_back(row);
        }

        table[0][0] = 0;
    }

    void DTWTable::printTable()
    {
        for (auto& row : table) {
            std::cout << "Row: \n";
            for (auto point : row) {
                std::cout << point << " ";
            }
        }
    }

    MeshUtil::Correspondence getCorrespondenceWarpingWindow(const vector<glm::vec3>& points,
                                                            const Contours::Contour& source,
                                                            const Contours::Contour& neighbour,
                                                            CostFunction costFunction,
                                                            double warpingWindowConstraint)
    {
        auto closestPair = Contours::findLowestXIndices(points, source, neighbour);

        Contours::Contour reorderedSource = Contours::reorderContourFrom(source, closestPair.first);
        Contours::Contour reorderedNeighbour = Contours::reorderContourFrom(neighbour, closestPair.second);

        DTWTable dtwTable;
        dtwTable.compute(points, reorderedSource, reorderedNeighbour, costFunction);

        auto warpingPath = dtwTable.getWarpingPathWindow(warpingWindowConstraint);

        MeshUtil::Correspondence correspondence;
        for (auto step : warpingPath) {
            pair<uint64_t, uint64_t> correspondingPair = std::make_pair(reorderedSource[step.first], reorderedNeighbour[step.second]);
            correspondence.emplace_back(correspondingPair);
        }

        return correspondence;
    }

    MeshUtil::Correspondence getCorrespondence(const vector<glm::vec3>& points,
                                               const Contours::Contour& source,
                                               const Contours::Contour& neighbour,
                                               CostFunction costFunction)
    {
        //auto closestPair = Contours::findClosestIndices(points, source, neighbour);
        auto closestPair = Contours::findLowestXIndices(points, source, neighbour);

        Contours::Contour reorderedSource = Contours::reorderContourFrom(source, closestPair.first);
        Contours::Contour reorderedNeighbour = Contours::reorderContourFrom(neighbour, closestPair.second);

        DTWTable dtwTable;
        dtwTable.compute(points, reorderedSource, reorderedNeighbour, costFunction);

        auto warpingPath = dtwTable.getWarpingPath();

        MeshUtil::Correspondence correspondence;

        for (auto step : warpingPath) {
            pair<uint64_t, uint64_t> correspondingPair = std::make_pair(reorderedSource[step.first], reorderedNeighbour[step.second]);
            correspondence.emplace_back(correspondingPair);
        }

        return correspondence;
    }

    vector<MeshUtil::TriangleIndices> getEdgeCaseTris(const vector<glm::vec3>& points,
                                                           const Contours::Contour& source,
                                                           const Contours::Contour& neighbour,
                                                           CostFunction costFunction,
                                                           pair<uint64_t, uint64_t> mergePoints)
    {
        vector<MeshUtil::TriangleIndices> edgeCaseTris;
        auto closestPair = Contours::findLowestXIndices(points, source, neighbour);

        Contours::Contour reorderedSource = Contours::reorderContourFrom(source, closestPair.first);
        Contours::Contour reorderedNeighbour = Contours::reorderContourFrom(neighbour, closestPair.second);

        DTWTable dtwTable;
        dtwTable.compute(points, reorderedSource, reorderedNeighbour, costFunction);

        auto warpingPath = dtwTable.getWarpingPath();

        return getEdgeCaseFromWarping(reorderedSource, reorderedNeighbour, warpingPath, mergePoints);
    }

    vector<MeshUtil::TriangleIndices> getEdgeCaseTrisWindow(const vector<glm::vec3>& points,
                                                      const Contours::Contour& source,
                                                      const Contours::Contour& neighbour,
                                                      CostFunction costFunction,
                                                      pair<uint64_t, uint64_t> mergePoints,
                                                      double warpingWindow)
    {
        vector<MeshUtil::TriangleIndices> edgeCaseTris;
        auto closestPair = Contours::findLowestXIndices(points, source, neighbour);

        Contours::Contour reorderedSource = Contours::reorderContourFrom(source, closestPair.first);
        Contours::Contour reorderedNeighbour = Contours::reorderContourFrom(neighbour, closestPair.second);

        DTWTable dtwTable;
        dtwTable.compute(points, reorderedSource, reorderedNeighbour, costFunction);

        auto warpingPath = dtwTable.getWarpingPathWindow(warpingWindow);

        return getEdgeCaseFromWarping(reorderedSource, reorderedNeighbour, warpingPath, mergePoints);
    }
}  // namespace DTW.