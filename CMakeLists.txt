# Require a recent version of cmake
cmake_minimum_required(VERSION 3.3.2 FATAL_ERROR)

# This project is C++ based.
project(tiago CXX)

# Instruct cmake to find the HPX settings
find_package(HPX)

add_hpx_executable(prog
    SOURCES prog.cpp heranca.cpp
    HEADERS heranca.hpp
    COMPONENT_DEPENDENCIES iostreams)

