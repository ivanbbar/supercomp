#include <iostream>
#include <fstream>
#include <vector>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <chrono>

int main() {
    std::string filename = "stocks.txt";

    std::ifstream input(filename);
    if (!input) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<double> hostData;
    double value;
    while (input >> value) {
        hostData.push_back(value);
    }

    auto start = std::chrono::high_resolution_clock::now();

    thrust::host_vector<double> hostVector(hostData.begin(), hostData.end());
    thrust::device_vector<double> deviceVector = hostVector;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cerr << "Time taken for allocation and copy: " << duration.count() << " seconds" << std::endl;

    std::cout << "Data copied to device vector." << std::endl;

    // Test the device vector, perform further computations if needed

    return 0;
}
