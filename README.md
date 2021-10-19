# cosc470code

This is the implementation of concepts developed in 
Cameron Stevenson, "Contour splitting for branching structures in CT image reconstructions", 2021
https://github.com/cstevenson3/cosc470writing/blob/main/report.pdf

David Mackay is the original author of the work in SurfaceReconstruction and TestModels. Refer to this paper:
D. Mackay, “Robust contour based surface reconstruction algorithms for applications
in medical imaging,” 2019.
https://ir.canterbury.ac.nz/handle/10092/16667

I am working on improvements to his method, and have modified his implementation.

## Structure
SurfaceReconstruction contains the C++ implementation of our methods.
Modifications contains my python code for testing ideas, and analysis tools.
TestModels contains original synthetic models under export as .ply, and contours sampled from them under sampled as .txt.

SurfaceReconstruction/src/Modifications.cpp contains the bulk of what I have added, with minimal modifications to other files to attach this code.

## Running Reconstructions

The README in SurfaceReconstruction is the original which came along with Mackay's implementation.

To build:
Make a directory SurfaceReconstruction/build.
Change to this directory.
cmake ..
make

To run:
From the directory above SurfaceReconstruction:
./SurfaceReconstruction/bin/surface_reconstruction

To reconstruct test models:
input "test" when prompted for input data format
Give a text file containing sampled contours (e.g. TestModels/sampled/csize_10/simple.txt)

## Configuring Reconstruction Method

Mackay's implementation offers contour merging and DTW, whilst my modifications provide contour splitting and point angle.

In main.cpp, change "PointCorrespondence::Algorithm::" to end with either "dynamictimewarpingwindow" or "pointangle" for the point correspondence method.

In Surface.cpp, change bool "CONTOUR_SPLITTING = " to either false or true to use merging or splitting for branching cases.

In Modifications.cpp, change "float ANG_WEIGHT = " to a value between 0 and 1 to indicate how much angle (and progression) should be weighted in the point angle method.