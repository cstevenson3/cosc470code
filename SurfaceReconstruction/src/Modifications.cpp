#include "Modifications.hpp"

namespace Modifications {
    std::vector<glm::vec3> getPointsFromContour(const std::vector<glm::vec3>& points,
                                                const Contours::Contour& contour) 
    {
        std::vector<glm::vec3> result = std::vector<glm::vec3>();
        for(auto index : contour) {
            result.push_back(points[index]);
        }
        return result;
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
        
    }

    MeshUtil::Correspondence pointCorrespondencePointAngle(const std::vector<glm::vec3>& points,
                                                            const Contours::Contour& source,
                                                            const Contours::Contour& neighbour) 
    {
        // simplify inputs for the algorithm
        std::vector<glm::vec3> contour1 = getPointsFromContour(points, source);
        std::vector<glm::vec3> contour2 = getPointsFromContour(points, neighbour);


    }
}  // namespace Modifications.