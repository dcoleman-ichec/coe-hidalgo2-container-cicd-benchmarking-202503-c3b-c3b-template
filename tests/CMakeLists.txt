add_executable(test_mpi3 test_mpi3.cpp)
target_include_directories(test_mpi3 PRIVATE 
    ${bmpi3_SOURCE_DIR}/include
    ${ut_SOURCE_DIR}/include
)
target_link_libraries(test_mpi3 PRIVATE bmpi3)
add_test(NAME test_mpi3-seq COMMAND test_mpi3)
add_test(NAME test_mpi3-mpi COMMAND mpirun --oversubscribe -np 4 test_mpi3)