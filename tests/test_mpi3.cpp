#include "mpi3/main.hpp"  // Provides boost::mpi3::main and communicator functionality
#include <boost/ut.hpp>   // Single-header unit testing framework

namespace mpi3 = boost::mpi3;
namespace ut   = boost::ut;

int mpi3::main(int argc, char** argv, mpi3::communicator world) {
    using namespace boost::ut;

    // Test 1: Ensure that the communicator's size is positive.
    "communicator size should be positive"_test = [&]{
        expect(world.size() > 0_i);
    };

    // Test 2: Ring Communication Test.
    // Each process sends its rank to its successor in a ring.
    "ring communication test"_test = [&] {
        const int size = world.size();
        const int rank = world.rank();

        // For a ring test, at least two processes are required.
        if(size < 2) {
            expect(true); // Trivial pass in a single-process run.
        } else {
            int send_value = rank;
            int recv_value = -1;
            // Calculate successor and predecessor in a cyclic ring.
            int successor   = (rank + 1) % size;
            int predecessor = (rank + size - 1) % size;
            
            // Perform send_receive: send our rank to our successor and receive from our predecessor.
            world.send_receive(&send_value, &send_value + 1, successor, &recv_value);
            
            // The received value should match the predecessor's rank.
            expect(recv_value == predecessor);
        }
    };

    return 0;
}