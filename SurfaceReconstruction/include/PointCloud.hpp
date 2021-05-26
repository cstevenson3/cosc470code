#ifndef SURFACE_RECONSTRUCTION_POINTCLOUD_HPP
#define SURFACE_RECONSTRUCTION_POINTCLOUD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <glm/vec3.hpp>

class PointCloud {
public:
    void addPoint(const glm::vec3&);
    void addPoints(std::vector<glm::vec3>&);
    std::string getString();
    void saveXYZFile(const std::string&);
private:
    std::vector<glm::vec3> points;
};


#endif //SURFACE_RECONSTRUCTION_POINTCLOUD_HPP
