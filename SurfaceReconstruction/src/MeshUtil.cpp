#include "MeshUtil.hpp"

namespace MeshUtil {
    using std::string;
    using std::vector;
    using std::pair;

    namespace {
        using std::multimap;

        bool doesTriangleContainIndex(TriangleIndices indices, uint64_t index)
        {
            return (indices.p1 == index) || (indices.p2 == index) || (indices.p3 == index);
        }

        string getplyHeader(uint64_t numVertices, uint64_t numFaces) {
            string header;
            header += "ply\n";
            header += "format ascii 1.0\n";
            header += "element vertex " + std::to_string(numVertices) + '\n';
            header += "property float x\n";
            header += "property float y\n";
            header += "property float z\n";
            header += "element face " + std::to_string(numFaces) + '\n';
            header += "property list uchar int vertex_index\n";
            header += "end_header\n";

            return header;
        }

        multimap<int, int> edgeListToReversedMultiMap(Correspondence correspondence)
        {
            multimap<int, int> outputMatching;

            for (auto matchingPair: correspondence) {
                outputMatching.emplace(matchingPair.second, matchingPair.first);
            }

            return outputMatching;
        }

        /**
         * Helper function that reverses the winding order of triangle indices.
         */
        TriangleIndices reverseTriangle(TriangleIndices tri)
        {
            TriangleIndices result{tri.p1, tri.p3, tri.p2};
            return result;
        }
    }  // namespace

    vector<TriangleIndices> triangulate(Correspondence correspondence, std::pair<uint64_t, uint64_t> omitVertices)
    {
        vector<TriangleIndices> triangles;
        for (uint64_t i = 0; i < correspondence.size(); i++) {
            auto current = correspondence[i].first;
            auto currentNeighbour = correspondence[i].second;
            auto nextIndex = i==correspondence.size()-1 ? 0 : i + 1;
            auto next = correspondence[nextIndex].first;
            auto nextNeighbour = correspondence[nextIndex].second;

            TriangleIndices t1{current, currentNeighbour, nextNeighbour};
            TriangleIndices t2{current, nextNeighbour, next};

            if (!(doesTriangleContainIndex(t1, omitVertices.first) &&
                  doesTriangleContainIndex(t1, omitVertices.second))) {
                triangles.emplace_back(t1);
            }

            if (!(doesTriangleContainIndex(t2, omitVertices.first) &&
                  doesTriangleContainIndex(t2, omitVertices.second))) {
                triangles.emplace_back(t2);
            }
        }

        return triangles;
    }

    vector<TriangleIndices> triangulateEdgeCase(Correspondence correspondence, pair<uint64_t, uint64_t> omitVertices,
            pair<uint64_t, uint64_t> nextVertices)
    {
        vector<TriangleIndices> triangles;

        auto edgeMap = edgeListToReversedMultiMap(std::move(correspondence));
        auto edgeCaseVertex1 = static_cast<uint64_t>(edgeMap.find(nextVertices.first)->second);
        auto edgeCaseVertex2 = static_cast<uint64_t>(edgeMap.find(nextVertices.second)->second);
        auto search = edgeMap.find(static_cast<int>(nextVertices.first));
        std::cout << "\n\n\n" << nextVertices.first << ", " << nextVertices.second << '\n';
        if (search != edgeMap.end()) {
            std::cout << "Found " << search->first << " " << search->second << '\n';
        } else {
            std::cout << "Not found\n";
        }

        TriangleIndices t1{omitVertices.first, edgeCaseVertex1, edgeCaseVertex2};
        TriangleIndices t2{omitVertices.second, edgeCaseVertex2, edgeCaseVertex1};

        triangles.emplace_back(t1);
        triangles.emplace_back(t2);

        return triangles;
    }

    vector<TriangleIndices> triangulate(Correspondence correspondence)
    {
        vector<TriangleIndices> triangles;
        for (uint64_t i = 0; i < correspondence.size(); i++) {
            auto current = correspondence[i].first;
            auto currentNeighbour = correspondence[i].second;
            auto nextIndex = i==correspondence.size()-1 ? 0 : i + 1;
            auto next = correspondence[nextIndex].first;
            auto nextNeighbour = correspondence[nextIndex].second;

            TriangleIndices t1{current, currentNeighbour, nextNeighbour};
            TriangleIndices t2{current, nextNeighbour, next};
            triangles.emplace_back(t1);
            triangles.emplace_back(t2);
        }

        return triangles;
    }

    void exportToPly(vector<glm::vec3> vertices, vector<TriangleIndices> triangles, const string& filename){
        std::ofstream ofs{filename, std::ofstream::out};

        string header = getplyHeader(vertices.size(), triangles.size());

        ofs << header;

        // Output vertices.
        for (auto vertex: vertices) {
            ofs << vertex.x << " " << vertex.y << " " << vertex.z << '\n';
        }

        // Output faces.
        for (auto triangle: triangles) {
            ofs << "3 " << triangle.p1 << " " << triangle.p2 << " " << triangle.p3 << '\n';
        }
    }

    vector<TriangleIndices> reverseTriangleOrder(vector<TriangleIndices> triangles)
    {
        vector<TriangleIndices> reversedTris;
        for (auto triangle : triangles) {
            TriangleIndices reversed = reverseTriangle(triangle);
            reversedTris.emplace_back(reversed);
        }

        return reversedTris;
    }
}  // namespace MeshUtil.