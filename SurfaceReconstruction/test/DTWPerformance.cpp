#include <gsl/gsl_util>
#include <random>
#include "DTW.hpp"
#include "ContourCorrespondence.hpp"
#include "Timer.hpp"
#include "catch.hpp"

namespace {
    using std::vector;
    using std::string;
    using Contours::Contour;
    using Contours::ContourList;
    using ContourCorrespondence::CorrespondenceMethod;

    SCENARIO("Performance testing for Dynamic Time Warping", "[Performance]") {
        GIVEN("Two randomly generated contours") {
            DTW::CostFunction costFunction = DTW::CostFunction::euclideanDistance;
            const CorrespondenceMethod correspondenceMethod = CorrespondenceMethod::centroidWithinRadius;
            const double min = -100.0;
            const double max = 100.0;

            const std::vector<uint64_t> sampleSizes{10, 100, 1000, 10000};

            std::random_device rd;  //Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
            std::uniform_real_distribution<> dis(min, max);

            WHEN("Point correspondence is performed") {
                for (auto numPoints: sampleSizes) {
                    vector<glm::vec3> points;
                    Contour c1;
                    Contour c2;
                    ContourList clist1;
                    ContourList clist2;

                    for (uint64_t i = 0; i < numPoints; i++) {
                        glm::vec3 newPoint{dis(gen), dis(gen), dis(gen)};
                        points.emplace_back(newPoint);
                        c1.emplace_back(i);
                    }

                    clist1.emplace_back(c1);

                    for (uint64_t j = 0; j < numPoints; j++) {
                        glm::vec3 newPoint{dis(gen), dis(gen), dis(gen)};
                        points.emplace_back(newPoint);
                        c2.emplace_back(j);
                    }

                    clist1.emplace_back(c2);

                    Timer timer;
                    timer.start();

                    auto contourCorrespondence = ContourCorrespondence::findContourCorrespondence(points,
                            clist1, clist2,
                            correspondenceMethod);

                    timer.stop();
                    timer.printElapsedTime("Contour correspondence for " + std::to_string(numPoints) + " points per contour.");

                    timer.start();

                    auto correspondence = DTW::getCorrespondence(points, c1, c2, costFunction);

                    timer.stop();
                    timer.printElapsedTime("Point correspondence for " + std::to_string(numPoints) + " points per contour.");
                }
            }
        }
    }
}