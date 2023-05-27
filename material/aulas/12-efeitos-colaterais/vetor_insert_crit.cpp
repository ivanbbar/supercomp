#include <vector>
#include <iostream>
#include <unistd.h>
#include <omp.h>

double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 10000;
    std::vector<double> vec;
    for (int i = 0; i < N; i++) {
        vec.push_back(0);  // Inicializa o vetor com elementos vazios
    }

    double start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double valor = conta_complexa(i);

        #pragma omp critical
        vec[i] = valor;
    }

    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    for (int i = 0; i < N; i++) {
        std::cout << vec[i] << " ";
    }

    std::cout << "\nTempo de execução: " << execution_time << " segundos" << std::endl;

    return 0;
}
