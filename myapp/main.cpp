#include "mpi3/main.hpp"
#include <iostream>
#include <format>

namespace mpi3 = boost::mpi3;

int mpi3::main(int, char**, mpi3::communicator world) {
    // Ensure at least 2 processes are available.
    if(world.size() < 2) {
        if(world.is_root()) {
            std::cerr << "This test requires at least 2 processes.\n";
        }
        return 1;
    }

    int size = world.size();
    int rank = world.rank();

    // In a ring: each process sends its rank to its successor,
    // and receives a value from its predecessor.
    int successor = (rank + 1) % size;
    int predecessor = (rank + size - 1) % size;

    // Each process prepares its value (its rank) to send.
    int send_value = rank;
    int recv_value = -1;

    // Use send_receive to simultaneously send and receive.
    // This sends 'send_value' to the successor and receives from the predecessor.
    world.send_receive(&send_value, &send_value + 1, successor, &recv_value);

    // Print the result.
    std::cout << std::format("Process {} received {} from process {}\n", rank, recv_value, predecessor);

    return 0;
}
