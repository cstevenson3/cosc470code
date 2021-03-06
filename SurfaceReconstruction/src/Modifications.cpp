#include "Modifications.hpp"

#include <iostream>
#include <string>
#include <limits>

#include "DTW.hpp"

#define PI 3.14159265f

namespace Modifications {
    void printVec(const glm::vec3& vec) 
    {
        std::cout << "(" + std::to_string(vec[0]) + ", " + std::to_string(vec[1]) + ", " + std::to_string(vec[2]) + ")" << std::endl;
    }

    void printContour(const std::vector<glm::vec3>& contour)
    {
        for(auto vec : contour) {
            printVec(vec);
            std::cout << std::endl;
        }
    }

    // Find m, b such that y = mx + b is best fit of points. 
    // Assumes points are centered on origin already
    glm::vec2 linearRegression(std::vector<glm::vec3>& points) 
    {
        float best_distance = std::numeric_limits<float>::infinity();
        float best_a = 1;
        float best_b = 1;
        for(int a = -10; a <= 10; a++) {
            for(int b = -10; b <= 10; b++) {
                float total_distance = 0;
                for(glm::vec3 p : points) {
                    float distance = abs(a * p[0] + b * p[1]) / sqrt(a * a + b * b);
                    total_distance += distance;
                }
                    
                if(total_distance < best_distance) {
                    best_distance = total_distance;
                    best_a = a;
                    best_b = b;
                }
            }
        }
        return glm::vec2(-best_a/best_b, 0.0);
    }

    // find angle between 0 and 1 where 0 is x-axis and 1 is full revolution
    float angleOfPoint(glm::vec3 point) 
    {
        if(point[0] == 0.0f) {  // on y-axis
            if(point[1] >= 0.0f) {
                return 0.25;
            } else {
                return 0.75;
            }
        }

        float ang = glm::atan(point[1] / point[0]);
        if(point[0] < 0.0f) {  // left half
            ang += PI;
        }
        if(point[0] >= 0 && point[1] < 0) {  // bottom right quadrant
            ang += 2 * PI;
        }
        return ang / (2 * PI);
    }

    std::vector<glm::vec3> translateContour(const std::vector<glm::vec3>& contour, 
                                            float x, 
                                            float y, 
                                            float z) 
    {
        std::vector<glm::vec3> result = std::vector<glm::vec3>();
        for(int i = 0; i < contour.size(); i++) {
            glm::vec3 point = contour[i];
            point[0] += x;
            point[1] += y;
            point[2] += z;
            result.push_back(point);
        }
        return result;
    }

    glm::vec3 rotatePoint(glm::vec3& p, float ang)
    {
        float xNew = p[0] * cos(ang) - p[1] * sin(ang);
        float yNew = p[0] * sin(ang) + p[1] * cos(ang);

        glm::vec3 pointNew = glm::vec3(xNew, yNew, p[2]);

        return pointNew;
    }

    std::vector<glm::vec3> rotateContour(std::vector<glm::vec3>& ctr, 
                                         float ang) 
    {
        std::vector<glm::vec3> output = std::vector<glm::vec3>();
        for(glm::vec3 point : ctr) {
            output.push_back(rotatePoint(point, ang));
        }
        return output;
    }

    std::vector<glm::vec3> getPointsFromContour(const std::vector<glm::vec3>& points,
                                                const Contours::Contour& contour) 
    {
        std::vector<glm::vec3> result = std::vector<glm::vec3>();
        for(auto index : contour) {
            // these modifications assume x and y are the contour planes, z is "up"
            // so we need to change coordinates
            glm::vec3 point = points[index];
            glm::vec3 shuffled = glm::vec3(0.0f, 0.0f, 0.0f);
            shuffled[0] = point[0];
            shuffled[1] = point[2];
            shuffled[2] = point[1];
            result.push_back(shuffled);
        }
        return result;
    }

    std::vector<glm::vec3> reorderFromIndex(const std::vector<glm::vec3>& contour, 
                                            int start)
    {
        std::vector<glm::vec3> result = std::vector<glm::vec3>();
        for(int i = 0; i < contour.size(); i++) {
            int index = (start + i) % contour.size();
            result.push_back(contour[index]);
        }
        return result;
    }

    int startingPoint(const std::vector<glm::vec3>& contour) 
    {
        // find starting candidates
        std::vector<int> candidates;
        for(int i = 0; i < contour.size(); i++) {
            int i1 = i;
            int i2 = (i + 1) % contour.size();
            glm::vec3 p1 = contour[i1];
            glm::vec3 p2 = contour[i2];
            if(p1[1] * p2[1] <= 0) {  // signs have swapped, so has crossed x-axis
                // point above x-axis is candidate
                if(p1[1] > 0) {
                    candidates.push_back(i1);
                } else {
                    candidates.push_back(i2);
                }
            }
        }

        if(candidates.size() == 0) {
            std::cout << "No candidates" << std::endl;
            printContour(contour);
            // throw NotImplemented();
            return 0; // hack to work on some bad contours in real data
        }

        // there should be at least one candidate if the centroid is correct and contour is continuous
        // find rightmost candidate
        int rightmost = candidates[0];
        glm::vec3 rightmostPoint = contour[rightmost];
        for(auto index : candidates) {
            glm::vec3 p = contour[index];
            if(p[0] > rightmostPoint[0]) {
                rightmost = index;
                rightmostPoint = p;
            }
        }
        return rightmost;
    }


    glm::vec3 contourCentroid(const std::vector<glm::vec3>& contour) 
    {
        std::vector<glm::vec3> triangleCentroids = std::vector<glm::vec3>();
        std::vector<float> triangleAreas = std::vector<float>();
        for(int i = 0; i < contour.size() - 2; i++) {
            glm::vec3 p0 = contour[0];
            glm::vec3 p1 = contour[i + 1];
            glm::vec3 p2 = contour[i + 2];

            glm::vec3 triangleCentroid = (p0 + p1 + p2) * (float)(1.0 / 3.0);
            float triangleArea = glm::cross(p1 - p0, p2 - p0)[2] * (float)(1.0 / 2.0);
            triangleCentroids.push_back(triangleCentroid);
            triangleAreas.push_back(triangleArea);
        }
        
        float totalArea = 0;
        glm::vec3 centroid = glm::vec3(0.0, 0.0, 0.0);
        for(int j = 0; j < triangleCentroids.size(); j++) {
            glm::vec3 triangleCentroid = triangleCentroids[j];
            float triangleArea = triangleAreas[j];

            glm::vec3 weightedCentroid = triangleCentroid * triangleArea;
            centroid = centroid + weightedCentroid;
            totalArea += triangleArea;
        }
        if(totalArea == 0) {
            std::cout << "Zero area contour" << std::endl;
            centroid = contour[0]; // hack to cope with errors in real data
            return centroid;
        }
        centroid = centroid * (float)(1.0 / totalArea);
        return centroid;
    } 

    std::vector<float> anglesInContour(const std::vector<glm::vec3>& contour) {
        std::vector<float> angles = std::vector<float>();
        for(auto point : contour) {
            angles.push_back(angleOfPoint(point));
        }
        return angles;
    }

    // ensure angle is always increasing
    std::vector<float> angleMonoticity(const std::vector<float>& angs) {
        std::vector<float> result(angs);
        for(int i = 0; i < result.size(); i++) {
            if(i == 0) {
                continue;
            }
            float angCurrent = result[i];
            float angPrevious = result[i - 1];
            if(angCurrent < angPrevious) {
                result[i] = angPrevious;
            }
        }
        return result;
    }

    std::vector<float> progressionAroundContour(const std::vector<glm::vec3>& contour) {
        std::vector<float> result = std::vector<float>();
        for(int i = 0; i < contour.size(); i++) {
            result.push_back( ((float)i) / contour.size() );
        }
        return result;
    }

    std::vector<float> weightedMetrics(std::vector<float> weights, 
                                                    std::vector<std::vector<float> > metrics)
    {
        std::vector<float> result = std::vector<float>(metrics[0].size(), 0);
        for(int w = 0; w < weights.size(); w++) {
            float weight = weights[w];
            std::vector<float> values = metrics[w];

            for(int i = 0; i < values.size(); i++) {
                result[i] += weight * values[i];
            }
        }
        return result;
    }

    MeshUtil::Correspondence pointCorrespondencePointAngle(const std::vector<glm::vec3>& contour1, 
                                                            const std::vector<glm::vec3>& contour2)
    {
        // could wrap all this preprocessing into a function so don't repeat code for both contours
        glm::vec3 centroid1 = contourCentroid(contour1);
        glm::vec3 centroid2 = contourCentroid(contour2);

        std::vector<glm::vec3> c1 = translateContour(contour1, -centroid1[0], -centroid1[1], 0);
        std::vector<glm::vec3> c2 = translateContour(contour2, -centroid2[0], -centroid2[1], 0);

        int c1start = startingPoint(c1);
        int c2start = startingPoint(c2);

        std::vector<glm::vec3> c1reordered = reorderFromIndex(c1, c1start);
        std::vector<glm::vec3> c2reordered = reorderFromIndex(c2, c2start);

        // angles of every point in contour
        std::vector<float> c1angs = anglesInContour(c1reordered);
        std::vector<float> c2angs = anglesInContour(c2reordered);

        c1angs = angleMonoticity(c1angs);
        c2angs = angleMonoticity(c2angs);

        // distance around contour by point count
        std::vector<float> c1prog = progressionAroundContour(c1reordered);
        std::vector<float> c2prog = progressionAroundContour(c2reordered);

        float ANG_WEIGHT = 0.5;
        std::vector<float> metricWeights = std::vector<float>();
        metricWeights.push_back(ANG_WEIGHT);  // weight angle by ANG_WEIGHT
        metricWeights.push_back(1 - ANG_WEIGHT);  // remaining weight given to progression

        std::vector<std::vector<float> > c1metricInputs = std::vector<std::vector<float> >();
        c1metricInputs.push_back(c1angs);
        c1metricInputs.push_back(c1prog);

        std::vector<std::vector<float> > c2metricInputs = std::vector<std::vector<float> >();
        c2metricInputs.push_back(c2angs);
        c2metricInputs.push_back(c2prog);

        std::vector<float> c1metrics = weightedMetrics(metricWeights, c1metricInputs);
        std::vector<float> c2metrics = weightedMetrics(metricWeights, c2metricInputs);


        // path finding
        int i = 0;
        int j = 0;
        std::vector<std::pair<int, int> > matches = std::vector<std::pair<int, int> >();
        matches.push_back(std::make_pair(0, 0));
        while(i < c1metrics.size() - 1 && j < c2metrics.size() - 1) {
            // advance i and j so the metrics leapfrog
            if(c1metrics[i] < c2metrics[j]) {
                i += 1;
            } else {
                j += 1;
            }
            matches.push_back(std::make_pair(i, j));
        }

        // triangle fan remaining points
        while(i < c1metrics.size()) {
            i += 1;
            matches.push_back(std::make_pair(i, j));
        }
        while(j < c2metrics.size()) {
            j += 1;
            matches.push_back(std::make_pair(i, j));
        }

        // undo reordering of contours
        MeshUtil::Correspondence matchesFixedOrder = MeshUtil::Correspondence();
        for(auto match : matches) {
            int i = (match.first + c1start) % c1metrics.size();
            int j = (match.second + c2start) % c2metrics.size();
            matchesFixedOrder.push_back(std::make_pair(i, j));
        }

        return matchesFixedOrder;
    }

    MeshUtil::Correspondence pointCorrespondencePointAngle(const std::vector<glm::vec3>& points,
                                                            const Contours::Contour& source,
                                                            const Contours::Contour& neighbour) 
    {
        // simplify inputs for the algorithm
        std::vector<glm::vec3> contour1 = getPointsFromContour(points, source);
        std::vector<glm::vec3> contour2 = getPointsFromContour(points, neighbour);

        MeshUtil::Correspondence correspondenceIndices = pointCorrespondencePointAngle(contour1, contour2);

        // convert back to original indices
        MeshUtil::Correspondence output = MeshUtil::Correspondence();
        for(auto pair : correspondenceIndices) {
            output.push_back(std::make_pair(source[pair.first], neighbour[pair.second]));
        }

        return output;
    }

    MeshUtil::Correspondence alignedDTW(const std::vector<glm::vec3>& points,
                                        const Contours::Contour& source,
                                        const Contours::Contour& neighbour)
    {
        // construct contours as point arrays
        std::vector<glm::vec3> ctr1 = getPointsFromContour(points, source);
        std::vector<glm::vec3> ctr2 = getPointsFromContour(points, neighbour);

        glm::vec3 centroid1 = contourCentroid(ctr1);
        glm::vec3 centroid2 = contourCentroid(ctr2);

        // align contours by position
        std::vector<glm::vec3> c1 = translateContour(ctr1, -centroid1[0], -centroid1[1], 0);
        std::vector<glm::vec3> c2 = translateContour(ctr2, -centroid2[0], -centroid2[1], 0);

        // find dominant direction of contour 1
        glm::vec2 c1regression = linearRegression(c1);
        float c1m = c1regression[0];

        // rotate both contours so that contour 1 is aligned with x axis
        float c1rad = atan(c1m);
        std::vector<glm::vec3> c1r = rotateContour(c1, -c1rad);
        std::vector<glm::vec3> c2r1 = rotateContour(c2, -c1rad);

        // rotate second contour to align with x axis
        glm::vec2 c2regression = linearRegression(c2r1);
        float c2m = c2regression[0];
        float c2rad = atan(c2m);
        std::vector<glm::vec3> c2r = rotateContour(c2r1, -c2rad);

        // prepare for DTW
        std::vector<glm::vec3> pointsNew = std::vector<glm::vec3>();
        Contours::Contour sourceNew = Contours::Contour();
        Contours::Contour neighbourNew = Contours::Contour();

        for(int i = 0; i < c1r.size(); i++) {
            glm::vec3 point = c1[i]; // translation only
            float temp = point[2];
            point[2] = point[1];
            point[1] = temp;
            pointsNew.push_back(point);
            sourceNew.push_back(i);
        }
        int start = c1r.size();
        for(int i = 0; i < c2r.size(); i++) {
            glm::vec3 point = c2[i]; // translation only
            float temp = point[2];
            point[2] = point[1];
            point[1] = temp;
            pointsNew.push_back(point);
            neighbourNew.push_back(start + i);
        }

        MeshUtil::Correspondence dtwCorrespondence = DTW::getCorrespondenceWarpingWindow(pointsNew, sourceNew, neighbourNew, DTW::CostFunction::euclideanDistance, 0.1);
        //MeshUtil::Correspondence dtwCorrespondence = pointCorrespondencePointAngle(pointsNew, sourceNew, neighbourNew);

        // convert back to original indices
        MeshUtil::Correspondence originalCorrespondence = MeshUtil::Correspondence();
        for(auto pair : dtwCorrespondence) {
            int a = pair.first;
            int b = pair.second;
            originalCorrespondence.push_back(std::make_pair(source[a], neighbour[b - start]));
        }

        return originalCorrespondence;
    }

    template <class T>
    bool vectorContains(std::vector<T>& vector, T element) {
        for(T item : vector) {
            if(item == element) {
                return true;
            }
        }
        return false;
    }

    template <class T>
    void appendWithoutDuplicates(std::vector<T>& vector, std::vector<T>& items) {
        for(T item : items) {
            if(vectorContains(vector, item)) {
                continue;
            } else {
                vector.push_back(item);
            }
        }
    }

    /**
     * Merge contour correspondences in both directions to give a list of pairs of lists of contour indices
     * Pairs represent connections between slices
    */
    std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t> > > mergeCorrepsondenceDirections(std::vector<ContourCorrespondence::CorrespondenceIndices>& forwardCorrespondence, 
                                                                                                         std::vector<ContourCorrespondence::CorrespondenceIndices>& reverseCorrespondence)
    {
        std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t> > > result = std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t> > >();
        
        // forward correspondences
        for(ContourCorrespondence::CorrespondenceIndices forward : forwardCorrespondence) {
            uint64_t from = forward.first;
            std::vector<uint64_t> fromVec = std::vector<uint64_t>();
            fromVec.push_back(from);
            std::vector<uint64_t> to = forward.second;
            bool merged = false;
            for(int j = 0; j < result.size(); j++) {
                if(vectorContains(result[j].first, from)) {
                    appendWithoutDuplicates(result[j].second, to);
                    merged = true;
                }
                for(uint64_t toItem : to) {
                    if(vectorContains(result[j].second, toItem)) {
                        appendWithoutDuplicates(result[j].first, fromVec);
                        appendWithoutDuplicates(result[j].second, to);
                        merged = true;
                    }
                }
            }
            if(!merged) {
                result.push_back(std::make_pair(fromVec, to));
            }
        }

        // reverse correspondences
        for(ContourCorrespondence::CorrespondenceIndices reverse : reverseCorrespondence) {
            uint64_t from = reverse.first;
            std::vector<uint64_t> fromVec = std::vector<uint64_t>();
            fromVec.push_back(from);
            std::vector<uint64_t> to = reverse.second;
            bool merged = false;
            for(int j = 0; j < result.size(); j++) {
                if(vectorContains(result[j].second, from)) {
                    appendWithoutDuplicates(result[j].first, to);
                    merged = true;
                }
                for(uint64_t toItem : to) {
                    if(vectorContains(result[j].first, toItem)) {
                        appendWithoutDuplicates(result[j].second, fromVec);
                        appendWithoutDuplicates(result[j].first, to);
                        merged = true;
                    }
                }
            }
            if(!merged) {
                result.push_back(std::make_pair(to, fromVec));
            }
        }

        return result;
    }

    void printIndices(std::vector<uint64_t>& indices)
    {
        std::cout << "[";
        for(auto index : indices) {
            std::cout << index;
            std::cout << ", ";
        }
        std::cout << "]";
    }

    void printJoint(std::pair<std::vector<uint64_t>, std::vector<uint64_t> >& joint)
    {
        std::cout << "(";
        printIndices(joint.first);
        std::cout << ", ";
        printIndices(joint.second);
        std::cout << ")";
    }

    void printMergedCorrespondence(std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t> > >& mc)
    {
        std::cout << "[";
        for(auto pair : mc) {
            printJoint(pair);
            std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    std::vector<Contours::Contour> splitContour(std::vector<glm::vec3>& points,
                                                Contours::Contour& contour, 
                                                Contours::Contour& neighbour1, 
                                                Contours::Contour& neighbour2)
    {
        std::vector<Contours::Contour> result = std::vector<Contours::Contour>();

        // METHOD
        // 0 = split halfway with no regard for direction
        // 1 = split halfway accounting for direction
        int METHOD = 1;
        switch(METHOD) {
            case 0: {
                if(contour.size() < 4) {
                    std::cout << "Contour too small too split" << std::endl;
                    result.push_back(contour);
                    result.push_back(contour);
                    return result;
                }

                int halfway = contour.size() / 2;
                Contours::Contour contour1 = Contours::Contour();
                Contours::Contour contour2 = Contours::Contour();
                for(int i = 0; i < halfway + 1; i++) {
                    contour1.push_back(contour[i]);
                }
                for(int i = halfway; i < contour.size(); i++) {
                    contour2.push_back(contour[i]);
                }
                // finish loops
                contour1.push_back(contour[0]);
                contour2.push_back(contour[0]); 
                contour2.push_back(contour[halfway]);

                result.push_back(contour1);
                result.push_back(contour2);
                break;
            }
            case 1: {
                // get slope by linear regression of all two-contour points
                // Contours::Contour twoContourIndices = Contours::mergeContours(points, neighbour1, neighbour2);
                // std::vector<glm::vec3> twoContour = getPointsFromContour(points, twoContourIndices);
                // glm::vec3 twoContourCentroid = contourCentroid(twoContour);
                // std::vector<glm::vec3> translatedTwoContour = translateContour(twoContour, -twoContourCentroid[0], -twoContourCentroid[1], 0);
                // glm::vec2 lrTwoContour = linearRegression(translatedTwoContour);
                // float slope = lrTwoContour[0];
                // float orthogonal = 9999;
                // if(slope != 0) {
                //     orthogonal = -1 / slope;
                // }

                // get slope by two-contour centroids
                std::vector<glm::vec3> n1 = getPointsFromContour(points, neighbour1);
                std::vector<glm::vec3> n2 = getPointsFromContour(points, neighbour2);
                glm::vec2 n1c = contourCentroid(n1);
                glm::vec2 n2c = contourCentroid(n2);

                float x = n2c[0] - n1c[0];
                float y = n2c[1] - n1c[1];

                float slope = 9999;
                if(x != 0) {
                    slope = y / x;
                }

                float orthogonal = 9999;
                if(y != 0) {
                    orthogonal = - x / y;
                }

                // LINE_METHOD
                // 0 = rotate single contour, sort points by x, divide by a vertical line (currently broken)
                // 1 = try different starting points and halfway points, find closest to orthogonal
                int LINE_METHOD = 1;
                switch(LINE_METHOD) {
                    case 0: {
                        std::vector<glm::vec3> oneContour = getPointsFromContour(points, contour);
                        // aligned dominant axis with x-axis,
                        float crad = atan(slope);
                        std::vector<glm::vec3> rotatedOneContour = rotateContour(oneContour, -crad);
                        // sort points by x
                        // TODO use standard functions
                        std::vector<std::pair<u_int64_t, glm::vec3> > contourSorted = std::vector<std::pair<u_int64_t, glm::vec3> >();
                        for(int i = 0; i < rotatedOneContour.size(); i++) {
                            glm::vec3 point = rotatedOneContour[i];
                            std::pair<u_int64_t, glm::vec3> pair = std::make_pair(contour[i], point);
                            bool added = false;
                            for(int j = 0; j < contourSorted.size(); j++) {
                                if(point[0] < contourSorted[j].second[0]) {
                                    contourSorted.insert(contourSorted.begin() + j, pair);
                                    added = true;
                                    break;
                                }
                            }
                            if(!added) {
                                contourSorted.push_back(pair);
                            }
                        }
                        // for now use halfway
                        int halfway = contourSorted.size() / 2;
                        Contours::Contour contour1 = Contours::Contour();
                        Contours::Contour contour2 = Contours::Contour();
                        for(int i = 0; i < halfway + 1; i++) {
                            contour1.push_back(contourSorted[i].first);
                        }
                        for(int i = halfway; i < contour.size(); i++) {
                            contour2.push_back(contourSorted[i].first);
                        }
                        // rerrange the contours back to correct order
                        std::sort(contour1.begin(), contour1.end());
                        std::sort(contour2.begin(), contour2.end());

                        // finish loops
                        contour1.push_back(contourSorted[0].first); 
                        contour2.push_back(contourSorted[0].first);
                        contour2.push_back(contourSorted[halfway].first);
                        // TODO check the contours are unbroken
                        
                        // TODO check which contours align better to which neighbours
                        result.push_back(contour2);
                        result.push_back(contour1);
                        break;
                    }
                    case 1: {
                        // use orthogonal to split single contour
                        std::vector<glm::vec3> oneContour = getPointsFromContour(points, contour);
                        int bestStartingIndex = 0;
                        int bestHalfwayIndex = 2;
                        float bestSlopeDifference = std::numeric_limits<float>::infinity();
                        for(int startingIndex = 0; startingIndex < contour.size(); startingIndex++) {
                            int halfwayIndex = (startingIndex + contour.size() / 2) % contour.size();

                            glm::vec3 startingPoint = oneContour[startingIndex];
                            glm::vec3 halfwayPoint = oneContour[halfwayIndex];

                            float candidateSlope = 9999;
                            float x = halfwayPoint[0] - startingPoint[0];
                            float y = halfwayPoint[1] - startingPoint[1];
                            if(x != 0) {
                                candidateSlope = y / x;
                            }
                            if(abs(candidateSlope - orthogonal) < bestSlopeDifference) {
                                bestSlopeDifference = abs(candidateSlope - orthogonal);
                                bestStartingIndex = startingIndex;
                                bestHalfwayIndex = halfwayIndex;
                            }
                        }

                        // split contour by best indices
                        int halfway = contour.size() / 2;
                        Contours::Contour contour1 = Contours::Contour();
                        Contours::Contour contour2 = Contours::Contour();
                        for(int i = 0; i < halfway; i++) {
                            int index = (bestStartingIndex + i) % contour.size();
                            contour1.push_back(contour[index]);
                        }
                        for(int i = halfway; i < contour.size(); i++) {
                            int index = (bestStartingIndex + i) % contour.size();
                            contour2.push_back(contour[index]);
                        }
                        // introduce new points along the split for a smoother correspondence
                        int numPointsToAdd = ceil(((float)contour.size()) / 3.141);
                        glm::vec3 point1 = points[contour[(bestStartingIndex + halfway) % contour.size()]];
                        glm::vec3 point2 = points[contour[(bestStartingIndex) % contour.size()]];
                        glm::vec3 pointOnNeighbour = points[neighbour1[0]];
                        float Ydiff = (pointOnNeighbour[1] - point1[1]);
                        //float scale = glm::distance(point1, point2);
                        float scale = 0.5 * Ydiff;  // how high to put the split curve peak
                        // along the line segment between these points
                        float t = 0;  // parameter from 0 to 1 along this line segment
                        std::vector<uint64_t> newPointIndices = std::vector<uint64_t>();
                        for(int n = 0; n < numPointsToAdd; n++) {
                            t = ((float)(n + 1)) / ((float)(numPointsToAdd + 1));
                            glm::vec3 newPoint = point1 + t * (point2 - point1);
                            // semicircle
                            newPoint[1] += scale * 2 * sqrt(0.25 - (t - 0.5) * (t - 0.5));
                            // quadratic
                            // newPoint[1] += scale * 4 * t * (1 - t);
                            points.push_back(newPoint);
                            newPointIndices.push_back(points.size() - 1);
                        }

                        // finish loops
                        contour1.push_back(contour[(bestStartingIndex + halfway) % contour.size()]);
                        for(auto index : newPointIndices) {
                            contour1.push_back(index);
                        }
                        contour1.push_back(contour[(bestStartingIndex) % contour.size()]);
                        contour2.push_back(contour[(bestStartingIndex) % contour.size()]);
                        std::reverse(newPointIndices.begin(), newPointIndices.end());
                        for(auto index : newPointIndices) {
                            contour2.push_back(index);
                        }
                        contour2.push_back(contour[(bestStartingIndex + halfway) % contour.size()]);

                        // choose contour arrangement
                        std::vector<glm::vec3> c1points = getPointsFromContour(points, contour1);
                        std::vector<glm::vec3> c2points = getPointsFromContour(points, contour2);
                        glm::vec2 c1c = contourCentroid(c1points);
                        glm::vec2 c2c = contourCentroid(c2points);
                        float arrangement1 = glm::length(c1c - n1c) + glm::length(c2c - n2c);
                        float arrangement2 = glm::length(c1c - n2c) + glm::length(c2c - n1c);
                        if(arrangement1 < arrangement2) {
                            result.push_back(contour1);
                            result.push_back(contour2);
                        } else {
                            result.push_back(contour2);
                            result.push_back(contour1);
                        }
                        
                        break;
                    }
                }
            }
        }

        return result;
    }

    std::vector<MeshUtil::TriangleIndices> contourSplitting(std::vector<glm::vec3>& points,
                                                            std::vector<Contours::Contour>& sourceContourList,
                                                            std::vector<Contours::Contour>& neighbourContourList,
                                                            std::vector<ContourCorrespondence::CorrespondenceIndices>& forwardCorrespondence, 
                                                            std::vector<ContourCorrespondence::CorrespondenceIndices>& reverseCorrespondence,
                                                            PointCorrespondence::Algorithm pointCorrespondenceMethod)
    {
        std::vector<MeshUtil::TriangleIndices> result = std::vector<MeshUtil::TriangleIndices>();
        std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t> > > mergedContourCorrespondence = mergeCorrepsondenceDirections(forwardCorrespondence, reverseCorrespondence);
        for(auto joint : mergedContourCorrespondence) {
            switch(joint.first.size()) {
                case 0: {
                    // unmatched contour
                    break;
                }
                case 1: {
                    switch(joint.second.size()) {
                        case 0: {
                            // unmatched contour
                            break;
                        }
                        case 1: {
                            // one to one
                            Contours::Contour source = sourceContourList[joint.first[0]];
                            Contours::Contour neighbour = neighbourContourList[joint.second[0]];
                            MeshUtil::Correspondence pc = PointCorrespondence::getPointCorrespondence(points, 
                                                                                                      source,
                                                                                                      neighbour,
                                                                                                      pointCorrespondenceMethod);
                            std::vector<MeshUtil::TriangleIndices> newTriangles = MeshUtil::triangulate(pc);                                                                
                            result.insert(result.end(), newTriangles.begin(), newTriangles.end());
                            break;
                        }
                        case 2: {
                            // one to two

                            Contours::Contour source = sourceContourList[joint.first[0]];
                            Contours::Contour neighbour1 = neighbourContourList[joint.second[0]];
                            Contours::Contour neighbour2 = neighbourContourList[joint.second[1]];

                            std::vector<Contours::Contour> splitted = splitContour(points,
                                                                                   source, 
                                                                                   neighbour1, 
                                                                                   neighbour2);
                            Contours::Contour source1 = splitted[0];
                            Contours::Contour source2 = splitted[1];

                            // run point correspondence for each side of split contour

                            MeshUtil::Correspondence pc1 = PointCorrespondence::getPointCorrespondence(points, 
                                                                                                       source1,
                                                                                                       neighbour1,
                                                                                                       pointCorrespondenceMethod);
                            std::vector<MeshUtil::TriangleIndices> newTriangles1 = MeshUtil::triangulate(pc1);                                                                
                            result.insert(result.end(), newTriangles1.begin(), newTriangles1.end());

                            MeshUtil::Correspondence pc2 = PointCorrespondence::getPointCorrespondence(points, 
                                                                                                       source2,
                                                                                                       neighbour2,
                                                                                                       pointCorrespondenceMethod);
                            std::vector<MeshUtil::TriangleIndices> newTriangles2 = MeshUtil::triangulate(pc2);                                                            
                            result.insert(result.end(), newTriangles2.begin(), newTriangles2.end());

                            break;
                        }
                        default: {
                            // one to many, unimplemented
                            break;
                        }
                    }
                    break;
                }
                case 2: {
                    switch(joint.second.size()) {
                        case 0: {
                            // unmatched contour
                            break;
                        }
                        case 1: {
                            // two to one
                            Contours::Contour neighbour = neighbourContourList[joint.second[0]];
                            Contours::Contour source1 = sourceContourList[joint.first[0]];
                            Contours::Contour source2 = sourceContourList[joint.first[1]];

                            std::vector<Contours::Contour> splitted = splitContour(points,
                                                                                   neighbour, 
                                                                                   source1, 
                                                                                   source2);
                            Contours::Contour neighbour1 = splitted[0];
                            Contours::Contour neighbour2 = splitted[1];

                            // run point correspondence for each side of split contour

                            MeshUtil::Correspondence pc1 = PointCorrespondence::getPointCorrespondence(points, 
                                                                                                       source1,
                                                                                                       neighbour1,
                                                                                                       pointCorrespondenceMethod);
                            std::vector<MeshUtil::TriangleIndices> newTriangles1 = MeshUtil::triangulate(pc1);                                                                
                            result.insert(result.end(), newTriangles1.begin(), newTriangles1.end());

                            MeshUtil::Correspondence pc2 = PointCorrespondence::getPointCorrespondence(points, 
                                                                                                       source2,
                                                                                                       neighbour2,
                                                                                                       pointCorrespondenceMethod);
                            std::vector<MeshUtil::TriangleIndices> newTriangles2 = MeshUtil::triangulate(pc2);                                                            
                            result.insert(result.end(), newTriangles2.begin(), newTriangles2.end());
                            break;
                        }
                        default: {
                            // 2 to many, unimplemented
                            break;
                        }
                    }
                    break;
                }
                default: {
                    // many to any, unimplemented
                    break;
                }
            }
        }
        return result;
    }
}  // namespace Modifications.