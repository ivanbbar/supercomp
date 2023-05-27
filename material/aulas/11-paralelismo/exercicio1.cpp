#include <iostream>
#include <unistd.h>
#include <omp.h>

double funcao1() {
    sleep(4);
    return 47;
}

double funcao2() {
    sleep(1);
    return -11.5;
}

int main() {
    double res_func1, res_func2;

    double inicio = omp_get_wtime();

    #pragma omp parallel num_threads(2)
    {
        #pragma omp single nowait
        {
            #pragma omp task
            res_func1 = funcao1();
        }

        #pragma omp single nowait
        {
            #pragma omp task
            res_func2 = funcao2();
        }
    }

    double fim = omp_get_wtime();
    double tempo_execucao = fim - inicio;

    std::cout << "Resultado da funcao1: " << res_func1 << std::endl;
    std::cout << "Resultado da funcao2: " << res_func2 << std::endl;
    std::cout << "Tempo de execucao: " << tempo_execucao << " segundos" << std::endl;

    return 0;
}
