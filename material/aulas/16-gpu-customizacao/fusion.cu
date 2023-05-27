#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <random>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/transform_reduce.h>

using namespace std::chrono;

struct Square
{
    __host__ __device__
    float operator()(const float& x) const
    {
        return x * x;
    }
};

void reportTime(const char* msg, steady_clock::duration span)
{
    auto ms = duration_cast<milliseconds>(span);
    std::cout << msg << " - levou - " << ms.count() << " milisegundos" << std::endl;
}

float magnitude(const thrust::device_vector<float>& v)
{
    float init = 0.0f;
    Square unary_op;
    thrust::plus<float> binary_op;

    return std::sqrt(thrust::transform_reduce(v.begin(), v.end(), unary_op, init, binary_op));
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << argv[0] << ": numero invalido de argumentos\n";
        std::cerr << "uso: " << argv[0] << "  tamanho do vetor\n";
        return 1;
    }
    int n = std::atoi(argv[1]); //numero de elementos
    steady_clock::time_point ts, te;

    // Criando um vector em thrust
    thrust::device_vector<float> v_d(n);

    // Inicializando o vector
    ts = steady_clock::now();
    std::generate(v_d.begin(), v_d.end(), std::rand);
    te = steady_clock::now();
    reportTime("Inicializacao", te - ts);

    // Calculando a magnitude do vetor
    ts = steady_clock::now();
    float len = magnitude(v_d);
    te = steady_clock::now();
    reportTime("Tempo para calculo", te - ts);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Magnitude : " << len << std::endl;

    return 0;
}
