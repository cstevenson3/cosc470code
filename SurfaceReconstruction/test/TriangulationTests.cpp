#include <glm/vec3.hpp>
#include "catch.hpp"

SCENARIO("Triangulation generation from matched edges.", "[Triangulation]") {
    GIVEN("A set of points, and a matching between these points") {
        glm::vec3 p0{0.0, 0.0, 1.0};
        glm::vec3 p1{1.0, 0.0, 0.0};
        glm::vec3 p2{0.0, 2.0, 1.0};
        glm::vec3 p3{1.0, 2.0, 0.0};
        // TODO(reimplement-test): Reimplement this.
//        ContourUtil::Contour contour(0);
//        contour.addPoint(p0);
//        contour.addPoint(p1);
//        ContourUtil::Contour neighbour(2);
//        neighbour.addPoint(p2);
//        neighbour.addPoint(p3);
        std::vector<std::pair<int, int>> matching;
        std::pair<int, int> match{0, 0};
        std::pair<int, int> match2{1, 1};
        matching.emplace_back(match);
        matching.emplace_back(match2);
        WHEN("Triangulation is generated.") {
//            Triangulation triangulation;
//            triangulation.generateTriangulationIndices(contour, neighbour, matching);
//            auto indices = triangulation.getTriangleIndices();
//            REQUIRE(indices.size() == 2);
//
//            THEN("Check first triangle.") {
//                auto triangle = indices[0];
//                REQUIRE(triangle.p1 == 0);
//                REQUIRE(triangle.p2 == 2);
//                REQUIRE(triangle.p3 == 3);
//            }
//
//            THEN("Check second triangle.") {
//                auto triangle = indices[1];
//                REQUIRE(triangle.p1 == 0);
//                REQUIRE(triangle.p2 == 3);
//                REQUIRE(triangle.p3 == 1);
//            }
        }
    }
}