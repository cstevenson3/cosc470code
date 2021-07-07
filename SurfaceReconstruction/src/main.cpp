#include <gsl/multi_span>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "Contours.hpp"
#include "PointCloud.hpp"
#include "ReconstructionConfig.hpp"
#include "Statistics.hpp"
#include "Surface.hpp"
#include "Timer.hpp"


namespace {
    using std::string;

    void testReal() {
        Statistics stats;
        Timer timer;

        timer.start();

        Surface::Reconstruction reconstruction;
        reconstruction.reconstructTwoWay(ContourCorrespondence::CorrespondenceMethod::centroidWithinRadius,
                                   PointCorrespondence::Algorithm::aligneddtw,
                                   "Output/real-match-aligned-dtw-10.ply");

        timer.stop();
        timer.printElapsedTime();

        stats.printStatistics();
    }
}  // namespace.

int main() {
    testReal();

    return 0;
}
