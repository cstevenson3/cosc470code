#ifndef SURFACE_RECONSTRUCTION_RECONSTRUCTOR_H
#define SURFACE_RECONSTRUCTION_RECONSTRUCTOR_H

#include "Contours.hpp"
#include "ContourCorrespondence.hpp"
#include "MeshUtil.hpp"
#include "PointCorrespondence.hpp"
#include "ReconstructionConfig.hpp"

namespace Surface {
    class Reconstruction {
    public:
        /**
         * Load contours from an input file and output a reconstructed mesh.
         * Attempts to perform a two way reconstruction.
         * @param correspondenceMethod      The type of contour correspondence to use.
         * @param pointCorrespondenceMethod The type of point correspondence to use.
         * @param exportFilename            The file to output reconstructed mesh to.
         */
        void reconstructTwoWay(ContourCorrespondence::CorrespondenceMethod, PointCorrespondence::Algorithm,
                                               const std::string& exportFilename);

        /**
         * Load contours from an input file and output a reconstructed mesh.
         * @param correspondenceMethod      The type of contour correspondence to use.
         * @param pointCorrespondenceMethod The type of point correspondence to use.
         * @param exportFilename            The file to output reconstructed mesh to.
         */
        void reconstruct(ContourCorrespondence::CorrespondenceMethod, PointCorrespondence::Algorithm,
                         const std::string& exportFilename);
    private:
        void loadContourStack(ReconstructionConfig::Configuration);
        Contours::Stack contourStack;
    };
}  // namespace Surface.


#endif //SURFACE_RECONSTRUCTION_RECONSTRUCTOR_H
