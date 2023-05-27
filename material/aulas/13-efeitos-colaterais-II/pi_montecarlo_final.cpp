#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>

double estimatePiMonteCarlo(int N) {
    int numThreads = omp_get_max_threads();
    int pointsPerThread = N / numThreads;
    int sum = 0;

    #pragma omp parallel reduction(+:sum)
    {
        unsigned int seed = static_cast<unsigned int>(omp_get_thread_num());
        std::default_random_engine gen(seed);
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        for (int i = 0; i < pointsPerThread; i++) {
            double x = dis(gen);
            double y = dis(gen);
            if (x * x + y * y <= 1) {
                sum += 1;
            }
        }
    }

    std::cerr << "sum = " << sum << std::endl;

    return 4.0 * sum / N;
}

int main() {
    int N = 100000;

    auto start = std::chrono::steady_clock::now();

    double pi = estimatePiMonteCarlo(N);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Estimated value of Pi: " << pi << std::endl;
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
