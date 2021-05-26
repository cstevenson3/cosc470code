#ifndef SURFACE_RECONSTRUCTION_MESHUTIL_H
#define SURFACE_RECONSTRUCTION_MESHUTIL_H

#include <cstdint>
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <vector>
#include <glm/vec3.hpp>

namespace MeshUtil {
    typedef std::vector<std::pair<uint64_t, uint64_t>> Correspondence;

    struct TriangleIndices {
        uint64_t p1;
        uint64_t p2;
        uint64_t p3;
    };

    enum class Direction {
        clockwise,
        counterclockwise
    };

    class TriangulationError: public std::logic_error {
    public:
        TriangulationError() : std::logic_error("Error while generating triangulation.") { };
    };

    /**
     * Triangulate, but omit triangles that include both the omit vertices. Useful for merged contours.
     * @param omitVertices  The pair of vertices to omit.
     * @return              A triangulation.
     */
    std::vector<TriangleIndices> triangulate(Correspondence, std::pair<uint64_t, uint64_t> omitVertices);

    /**
     * Create a triangulation from a point correspondence between two contours.
     * @param correspondence    Correspondence between two contours.
     * @return                  Triangle indices for the mesh.
     */
    std::vector<TriangleIndices> triangulate(Correspondence correspondence);

    /**
     * Generate triangles for the edge case encountered in merged contours (for example in branching).
     * @param correspondence    The point correspondence.
     * @param omitVertices      The vertices which were omitted from general triangulation.
     * @param nextVertices      The next vertex matchings.
     * @return                  Triangles as triangle indices.
     */
    std::vector<TriangleIndices> triangulateEdgeCase(Correspondence correspondence, std::pair<uint64_t, uint64_t> omitVertices,
        std::pair<uint64_t, uint64_t> nextVertices);

    /**
     * Export the mesh to ply format.
     * @param vertices  The global vertex set.
     * @param triangles A vector of triangle indices.
     * @param filename  The filename to output to.
     */
    void exportToPly(std::vector<glm::vec3> vertices, std::vector<TriangleIndices> triangles, const std::string& filename);

    /**
     * Reverses the ordering of triangles. Can be used to reverse normals.
     * @param triangles The set of triangle indices to reverse.
     * @return          A reversed order set of triangles.
     */
    std::vector<TriangleIndices> reverseTriangleOrder(std::vector<TriangleIndices> triangles);
}


#endif //SURFACE_RECONSTRUCTION_MESHUTIL_H
