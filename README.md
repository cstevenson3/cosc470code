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

Mackay's implementation offers contour merging and DTW, whilst my modifications provide contour splitting and point angle. To minimise editing of the original code I haven't added method type as a command line option, so the binary must be recompiled for a particular method.

In main.cpp, change "PointCorrespondence::Algorithm::" to end with either "dynamictimewarpingwindow" or "pointangle" for the point correspondence method.

In Surface.cpp, change bool "CONTOUR_SPLITTING = " to either false or true to use merging or splitting for branching cases.

In Modifications.cpp, change "float ANG_WEIGHT = " to a value between 0 and 1 to indicate how much angle (and progression) should be weighted in the point angle method.

## Analysis Tools

Provided in Modifications/analysis is a tool for automating reconstruction and analysis of models.
Use the repo root as the working directory.
A single run of reconstruction_automation.py uses whatever binary is currently compiled, so to test multiple methods you will need to change the C++ source and recompile the reconstruction binary, then rerun reconstruction_automation.py.

The first few options in config.json are what to do in a single run.
"label" is the reconstruction method which is currently being used for reconstruct, analyse, and take_snapshots.
"reconstuct" runs the reconstruction binary to generate reconstructed models (stored in Output/automation)
"take_snapshots" opens these reconstructions in PyMeshLab's rendering tool and takes snapshots (stored in Output/automation/snapshots)
"analyse" uses PyMeshLab to run Hausdorff distance metrics between reconstructions and their originals. Results are stored in Output/automation/stats.json. The runs used for the report for this project are stored in the stats.json supplied with this repo. "reconstruct" must have been run first
"show_stats" runs whatever you want to investigate in reconstruction_automation.show_stats. As an example a particular model and plane sample count can be picked out, and hd_faces_reverse.mean shown for all methods analysed.
"compare_labels" compares the accuracy of two reconstruction methods which have been reconstructed and analysed. As an example, it outputs -15.2 for dtw and cspa50, meaning cspa50 improves by 15% on DTW for the models included.
"append_to_stats" if set to False, the stats.json will be wiped on a run of analyse. If set to true, analyse will append to the existing stats, which is necessary for storing results for two reconstruction methods.
"performance_test" can be used to call a particular reconstruction multiple times to get average times for that method

Some other options:
"output_file" is where the reconstruction binary puts its output, since this is hardcoded.
"test_model_names" and "plane_samples" are the models and plane counts which should be reconstructed, analysed etc. This requires matching names for originals .ply and their plane sample .txt files. It also expects the directory structure $(test_model_samples_folder)/$(sample_prefix)$(plane_count)/$(model_name).txt, as provided in this repo.



