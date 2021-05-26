set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(RECONSTRUCTION_SRCS main.cpp
        ReconstructionConfig.cpp ../include/ReconstructionConfig.hpp
        Timer.cpp ../include/Timer.hpp
        Statistics.cpp ../include/Statistics.hpp
        ContourStatistics.cpp ../include/ContourStatistics.hpp
        PointCloud.cpp ../include/PointCloud.hpp
        DTW.cpp ../include/DTW.hpp
        PointCorrespondence.cpp ../include/PointCorrespondence.hpp
        Contours.cpp ../include/Contours.hpp
        PointUtil.cpp ../include/PointUtil.hpp
        MeshUtil.cpp ../include/MeshUtil.hpp
        Surface.cpp ../include/Surface.hpp
        ContourCorrespondence.cpp ../include/ContourCorrespondence.hpp
        ../include/EmptyContour.hpp
        ../include/ReconstructionErrors.hpp)

add_executable(surface_reconstruction ${RECONSTRUCTION_SRCS})

set_target_properties(
  surface_reconstruction PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_FLAGS "${WARNING_FLAGS}"
)

if(CLANG_TIDY_EXE)
  set_target_properties(
    surface_reconstruction PROPERTIES
    CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
  )
endif()


# Add a static library that can be used for testing.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
add_library(lib_surface_reconstruction STATIC ${RECONSTRUCTION_SRCS})



if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(surface_reconstruction PRIVATE "-Wall")
    target_compile_options(surface_reconstruction PRIVATE "-Werror")
    target_compile_options(surface_reconstruction PRIVATE "-pedantic")
endif()
