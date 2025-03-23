cmake_minimum_required(VERSION 3.10)
project(MPIHelloWorld LANGUAGES CXX)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the MPI package
find_package(MPI REQUIRED)

# Fetch boost-mpi3 (header-only library)
include(FetchContent)
FetchContent_Declare(bmpi3 GIT_REPOSITORY https://gitlab.com/correaa/boost-mpi3.git) 
FetchContent_MakeAvailable(bmpi3)

# Fetch boost::ut (header-only testing framework)
FetchContent_Declare(
    ut
    GIT_REPOSITORY https://github.com/boost-ext/ut.git
    GIT_TAG master  
)
FetchContent_MakeAvailable(ut)

add_subdirectory(myapp)

enable_testing()
add_subdirectory(tests)


