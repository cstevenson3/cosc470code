#include <catch.hpp>
#include <glm/vec3.hpp>

SCENARIO( "Contour can be created.", "[Contour]" ) {
    // TODO(reimplement-tests): Reimplement these.
    GIVEN( "A set of input points." ) {
        std::vector<glm::vec3> points;
        glm::vec3 p1{0.0, 0.0, 1.0};
        glm::vec3 p2{1.0, 0.0, 0.0};
        glm::vec3 p3{1.0, 0.0, 1.0};

        points.emplace_back(p1);
        points.emplace_back(p2);
        points.emplace_back(p3);

        size_t offset = 0;
//        ContourUtil::Contour contour(offset);
//
//        contour.addPoint(p1);
//
//        REQUIRE( contour.getPoints().size() == 1);
//        REQUIRE( contour.getPoints()[0] == p1 );
//
//        WHEN( "Points are added." ) {
//            contour.addPoint(p2);
//
//
//            THEN( "the size and capacity change" ) {
//                REQUIRE( contour.getPoints().size() == 2 );
//            }
//        }
//        WHEN( "the size is reduced" ) {
//            contour.addPoint(p3);
//
//            THEN( "the size changes but not capacity" ) {
//                REQUIRE( contour.getPoints().size() == 2 );
//            }
//        }
    }

    GIVEN( "A set of input points" ) {
        glm::vec3 p1{0.0, 0.0, 3.0};
        glm::vec3 p2{-2.0, 0.0, 0.0};
        glm::vec3 p3{2.0, 0.0, 3.0};

        size_t offset = 0;
//        ContourUtil::Contour contour(offset);
//
//        contour.addPoint(p1);
//        contour.addPoint(p2);
//        contour.addPoint(p3);
//
//        WHEN( "The contour centroid is computed" ) {
//            auto centroid = contour.computeCentroid();
//            THEN ("It is computed correctly" ) {
//                REQUIRE( centroid.x == Approx(0.0) );
//                REQUIRE( centroid.y == Approx(0.0) );
//                REQUIRE( centroid.z == Approx(2.0) );
//            }
//        }
    }
}