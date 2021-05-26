#include <gsl/gsl_util>
#include <random>
#include <DTW.hpp>
#include <ContourCorrespondence.hpp>
#include <Surface.hpp>
#include "Timer.hpp"
#include "catch.hpp"


namespace {
    using std::vector;
    using DTW::CostFunction;
    using ContourCorrespondence::CorrespondenceMethod;
    using Contours::Contour;
    using Contours::ContourList;

    SCENARIO("Performance testing with number of contours varied.", "[Performance]") {
        // Initialize constants.
        const CorrespondenceMethod correspondenceMethod = CorrespondenceMethod::centroidWithinRadius;
        const double min = -100.0;
        const double max = 100.0;

        const uint64_t pointsPerContour = 50;  // Hold this fixed for this testing.
        const std::vector<uint64_t> sampleSizes{10, 100, 1000};

        // Random point generation.
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(min, max);



        for (auto contoursPerSlice : sampleSizes) {
            vector<glm::vec3> points;
            ContourList clist1;
            ContourList clist2;

            for (uint64_t slice = 0; slice < contoursPerSlice; slice++) {
                Contour contour;
                for (uint64_t i = 0; i < pointsPerContour; i++) {
                    glm::vec3 newPoint{dis(gen), dis(gen), dis(gen)};
                    points.emplace_back(newPoint);
                    contour.emplace_back(i);
                }

                clist1.emplace_back(contour);
            }


            for (uint64_t slice = 0; slice < contoursPerSlice; slice++) {
                Contour contour;
                for (uint64_t i = 0; i < pointsPerContour; i++) {
                    glm::vec3 newPoint{dis(gen), dis(gen), dis(gen)};
                    points.emplace_back(newPoint);
                    contour.emplace_back(i);
                }

                clist2.emplace_back(contour);
            }

            Timer timer;
            timer.start();

            auto contourCorrespondence = ContourCorrespondence::findContourCorrespondence(points,
                                                                                          clist1, clist2,
                                                                                          correspondenceMethod);

            timer.stop();
            timer.printElapsedTime("Contour correspondence for " + std::to_string(contoursPerSlice) + " contours per slice.");
        }

    }
}  // namespace.