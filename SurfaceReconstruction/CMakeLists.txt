cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)

find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
  DOC "Path to clang-tidy executable"
  )
if(NOT CLANG_TIDY_EXE)
  message(STATUS "clang-tidy not found.")
else()
  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
  set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*,-fuchsia-default-arguments")
endif()

project(surface_reconstruction)
include_directories(include include/gsl)
add_subdirectory(src)

# Perform tests.
add_subdirectory(test)
