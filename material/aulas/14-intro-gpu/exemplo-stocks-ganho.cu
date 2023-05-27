#include <iostream>
#include <fstream>
#include <vector>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>

struct Difference : public thrust::binary_function<double, double, double>
{
    __host__ __device__
    double operator()(const double& a, const double& b) const
    {
        return b - a;
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

    // Imprimir as diferenças diárias
    std::cout << "Daily gains:" << std::endl;
    for (thrust::device_vector<double>::iterator it = dailyGain.begin(); it != dailyGain.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}
