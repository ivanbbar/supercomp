#include <iostream>
#include <fstream>
#include <vector>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/count.h>
#include <thrust/functional.h>
#include <thrust/reduce.h>

struct Difference : public thrust::binary_function<double, double, double>
{
    __host__ __device__
    double operator()(const double& a, const double& b) const
    {
        return b - a;
    }
};

struct GreaterThanZero
{
    __host__ __device__
    bool operator()(const double& value) const
    {
        return value > 0.0;
    }
};

struct SumPositive
{
    __host__ __device__
    double operator()(const double& a, const double& b) const
    {
        return (b > 0.0) ? a + b : a;
    }
};

int main()
{
    std::string filename = "stocks.txt";

    // Ler os dados do arquivo e armazenar em um vetor
    std::ifstream input(filename);
    if (!input)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<double> stockData;
    double price;
    while (input >> price)
    {
        stockData.push_back(price);
    }

    size_t dataSize = stockData.size();

    // Criar os device_vectors a partir dos dados do host
    thrust::device_vector<double> stockDevice(stockData.begin(), stockData.end());

    // Criar o vetor das diferenças diárias
    thrust::device_vector<double> dailyGain(dataSize - 1);
    thrust::transform(stockDevice.begin(), stockDevice.end() - 1, stockDevice.begin() + 1, dailyGain.begin(), Difference());

    // Contar quantas vezes o valor subiu
    int countSubiu = thrust::count_if(dailyGain.begin(), dailyGain.end(), GreaterThanZero());

    // Calcular o aumento médio considerando apenas as vezes em que o valor aumentou
    double aumentoMedio = thrust::reduce(dailyGain.begin(), dailyGain.end(), 0.0, SumPositive()) / countSubiu;

    // Imprimir os resultados
    std::cout << "Quantidade de vezes que o valor subiu: " << countSubiu << std::endl;
    std::cout << "Aumento médio considerando apenas as vezes em que o valor aumentou: " << aumentoMedio << std::endl;

    return 0;
}
