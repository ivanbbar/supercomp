#include <iostream>
#include <fstream>
#include <vector>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/count.h>
#include <thrust/functional.h>
#include <thrust/replace.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/iterator/transform_iterator.h>

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

struct ReplaceNegative
{
    __host__ __device__
    double operator()(const double& value) const
    {
        return (value > 0.0) ? value : 0.0;
    }
};

struct Sum
{
    __host__ __device__
    double operator()(const double& a, const double& b) const
    {
        return a + b;
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

    // Substituir valores negativos por 0
    thrust::replace_if(dailyGain.begin(), dailyGain.end(), dailyGain.begin(), thrust::placeholders::_1 < 0.0, 0.0);

    // Calcular a média dos valores positivos
    int countPositivos = thrust::count_if(dailyGain.begin(), dailyGain.end(), GreaterThanZero());
    double somaPositivos = thrust::reduce(dailyGain.begin(), dailyGain.end(), 0.0, Sum());

    double mediaPositivos = somaPositivos / countPositivos;

    // Imprimir o resultado
    std::cout << "Média dos valores positivos: " << mediaPositivos << std::endl;

    return 0;
}
