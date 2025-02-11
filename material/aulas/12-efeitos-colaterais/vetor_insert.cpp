#include <vector>
#include <iostream>
#include <unistd.h>
#include <ctime>

double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 10000;
    std::vector<double> vec;
    for (int i = 0; i < N; i++) {
        vec.push_back(0);  // Inicializa o vetor com elementos vazios
    }

    clock_t start_time = clock();

    for (int i = 0; i < N; i++) {
        double valor = conta_complexa(i);
        vec[i] = valor;
    }

    clock_t end_time = clock();
    double execution_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    for (int i = 0; i < N; i++) {
        std::cout << vec[i] << " ";
    }

    std::cout << "\nTempo de execução: " << execution_time << " segundos" << std::endl;

    return 0;
}
