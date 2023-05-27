#include <iostream>
#include <random>
#include <chrono>

double estimatePiMonteCarlo(int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    int sum = 0;
    for (int i = 0; i < N; i++) {
        double x = dis(gen);
        double y = dis(gen);
        if (x * x + y * y <= 1) {
            sum += 1;
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
