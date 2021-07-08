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
        for(int a = 0; a < 10; a++) {
            for(int b = 0; b < 10; b++) {
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
                                            float z) {
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
            if(p1[1] * p2[1] < 0) {  // signs have swapped, so has crossed x-axis
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
            throw NotImplemented();
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

        float ANG_WEIGHT = 0.9;
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
        std::vector<glm::vec3> ctr1 = std::vector<glm::vec3>();
        std::vector<glm::vec3> ctr2 = std::vector<glm::vec3>();
        for(int i = 0; i < source.size(); i++) {
            ctr1.push_back(points[source[i]]);
            // rearrange vertex order
            float temp = ctr1[i][2];
            ctr1[i][2] = ctr1[i][1];
            ctr1[i][1] = temp;
        }
        for(int i = 0; i < neighbour.size(); i++) {
            ctr2.push_back(points[neighbour[i]]);
            float temp = ctr2[i][2];
            ctr2[i][2] = ctr2[i][1];
            ctr2[i][1] = temp;
        }

        printContour(ctr1);

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
            glm::vec3 point = c1r[i];
            float temp = point[2];
            point[2] = point[1];
            point[1] = temp;
            pointsNew.push_back(point);
            sourceNew.push_back(i);
        }
        int start = c1r.size();
        for(int i = 0; i < c2r.size(); i++) {
            glm::vec3 point = c1r[i];
            float temp = point[2];
            point[2] = point[1];
            point[1] = temp;
            pointsNew.push_back(point);
            neighbourNew.push_back(start + i);
        }

        MeshUtil::Correspondence dtwCorrespondence = DTW::getCorrespondenceWarpingWindow(pointsNew, sourceNew, neighbourNew, DTW::CostFunction::euclideanDistance, 0.1);
        // MeshUtil::Correspondence dtwCorrespondence = pointCorrespondencePointAngle(pointsNew, sourceNew, neighbourNew);

        // convert back to original indices
        for(auto pair : dtwCorrespondence) {
            int a = pair.first;
            int b = pair.second;
            pair.first = source[a];
            pair.second = neighbour[b - start];
        }

        return dtwCorrespondence;
    }
}  // namespace Modifications.