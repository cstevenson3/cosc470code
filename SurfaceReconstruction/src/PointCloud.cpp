#include "PointCloud.hpp"

using std::vector;
using std::string;
using std::to_string;


// Add a point to the point cloud.
void PointCloud::addPoint(const glm::vec3& point) {
    points.push_back(point);
}

void PointCloud::addPoints(vector<glm::vec3>& newPoints) {
    points.insert(points.end(), newPoints.begin(), newPoints.end());
}

// Returns values of the point cloud as a human readable string. Useful for testing.
string PointCloud::getString(){
    string result;
    result.append("Points in point cloud: \n");
    for (auto point: points) {
        result.append("\tX: ");
        result.append(to_string(point.x));
        result.append(", Y: ");
        result.append(to_string(point.y));
        result.append(", Z: ");
        result.append(to_string(point.z));
        result.append("\n");
    }

    result.append("\n");

    return result;
}

void PointCloud::saveXYZFile(const std::string & filename) {
    std::ofstream outFile;
    outFile.open(filename, std::ios_base::out);

    for (auto point: points) {
        outFile << to_string(point.x) + " ";
        outFile << to_string(point.y) + " ";
        outFile << to_string(point.z) << "\n";
    }

    outFile.close();
}