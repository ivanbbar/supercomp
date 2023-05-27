#include <iostream>
#include <omp.h>

double calcular_pi_parallel(int n, int num_threads) {
    double pi = 0.0;
    double partial_sum[num_threads];

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        int start = thread_id * (n / num_threads) + 1;
        int end = (thread_id + 1) * (n / num_threads) + 1;
        double sinal = (thread_id % 2 == 0) ? 1.0 : -1.0;
        double sum = 0.0;

        for (int i = start; i < end; i++) {
            double termo = 1.0 / (2 * i - 1);
            sum += sinal * termo;
            sinal *= -1.0;
        }

        partial_sum[thread_id] = sum;
    }

    for (int i = 0; i < num_threads; i++) {
        pi += partial_sum[i];
    }

    return pi * 4.0;
}

double calcular_pi_parallel2(int n) {
    double pi = 0.0;

    #pragma omp parallel for reduction(+:pi)
    for (int i = 1; i <= n; i++) {
        double termo = 1.0 / (2 * i - 1);
        double sinal = (i % 2 == 0) ? -1.0 : 1.0;
        pi += sinal * termo;
    }

    return pi * 4.0;
}

int main() {
    int n = 1000000000;
    int num_threads = 2;

    double inicio = omp_get_wtime();
    double resultado = calcular_pi_parallel(n,num_threads);
    // double resultado = calcular_pi_parallel2(n);
    double fim = omp_get_wtime();

    double tempo_execucao = fim - inicio;

    std::cout << "Valor aproximado de π: " << resultado << std::endl;
    std::cout << "Tempo de execução: " << tempo_execucao << " segundos" << std::endl;

    return 0;
}
