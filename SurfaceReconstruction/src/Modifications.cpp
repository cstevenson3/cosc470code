#include "Modifications.hpp"

#define PI 3.14159265f

namespace Modifications {
    // find angle between 0 and 1 where 0 is x-axis and 1 is full revolution
    float angle_of_point(glm::vec3 point) 
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

    std::vector<glm::vec3> translate_contour(const std::vector<glm::vec3>& contour, float x, float y, float z) {
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

    std::vector<glm::vec3> getPointsFromContour(const std::vector<glm::vec3>& points,
                                                const Contours::Contour& contour) 
    {
        std::vector<glm::vec3> result = std::vector<glm::vec3>();
        for(auto index : contour) {
            result.push_back(points[index]);
        }
        return result;
    }

    std::vector<glm::vec3> reorder_from_index(const std::vector<glm::vec3>& contour, int start)
    {
        std::vector<glm::vec3> result = std::vector<glm::vec3>();
        for(int i = 0; i < contour.size(); i++) {
            int index = (start + i) % contour.size();
            result.push_back(contour[index]);
        }
        return result;
    }

    int starting_point(const std::vector<glm::vec3>& contour) 
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

        // there should be at least one candidate if the centroid is correct and contour is continuous
        // find rightmost candidate
        int rightmost = candidates[0];
        glm::vec3 rightmost_point = contour[rightmost];
        for(auto index : candidates) {
            glm::vec3 p = contour[index];
            if(p[0] > rightmost_point[0]) {
                rightmost = index;
                rightmost_point = p;
            }
        }
        return rightmost;
    }


    glm::vec3 contour_centroid(const std::vector<glm::vec3>& contour) 
    {
        std::vector<glm::vec3> triangle_centroids = std::vector<glm::vec3>();
        std::vector<float> triangle_areas = std::vector<float>();
        for(int i = 0; i < contour.size() - 2; i++) {
            glm::vec3 p0 = contour[0];
            glm::vec3 p1 = contour[i + 1];
            glm::vec3 p2 = contour[i + 2];

            glm::vec3 triangle_centroid = (p0 + p1 + p2) * (float)(1.0 / 3.0);
            float triangle_area = glm::cross(p1 - p0, p2 - p0)[2] * (float)(1.0 / 2.0);
            triangle_centroids.push_back(triangle_centroid);
            triangle_areas.push_back(triangle_area);
        }
        
        float total_area = 0;
        glm::vec3 centroid = glm::vec3(0.0, 0.0, 0.0);
        for(int j = 0; j < triangle_centroids.size(); j++) {
            glm::vec3 triangle_centroid = triangle_centroids[j];
            float triangle_area = triangle_areas[j];

            glm::vec3 weighted_centroid = triangle_centroid * triangle_area;
            centroid = centroid + weighted_centroid;
            total_area += triangle_area;
        }
        centroid = centroid * (float)(1.0 / total_area);
        return centroid;
    } 

    MeshUtil::Correspondence pointCorrespondencePointAngle(const std::vector<glm::vec3>& contour1, 
                                                            const std::vector<glm::vec3>& contour2)
    {
        glm::vec3 centroid1 = contour_centroid(contour1);
        glm::vec3 centroid2 = contour_centroid(contour2);

        std::vector<glm::vec3> c1 = translate_contour(contour1, -centroid1[0], -centroid1[1], 0);
        std::vector<glm::vec3> c2 = translate_contour(contour2, -centroid2[0], -centroid2[1], 0);
    }

    MeshUtil::Correspondence pointCorrespondencePointAngle(const std::vector<glm::vec3>& points,
                                                            const Contours::Contour& source,
                                                            const Contours::Contour& neighbour) 
    {
        // simplify inputs for the algorithm
        std::vector<glm::vec3> contour1 = getPointsFromContour(points, source);
        std::vector<glm::vec3> contour2 = getPointsFromContour(points, neighbour);

        MeshUtil::Correspondence correspondence_indices = pointCorrespondencePointAngle(contour1, contour2);

        // convert back to original indices
        MeshUtil::Correspondence output = MeshUtil::Correspondence();
        for(auto pair : correspondence_indices) {
            output.push_back(std::make_pair(source[pair[0]], neighbour[pair[1]]));
        }

        return output;
    }
}  // namespace Modifications.