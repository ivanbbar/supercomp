#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/iterator/discard_iterator.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/sequence.h>
#include <thrust/reduce.h>

// Função para calcular a diferença entre dois valores
struct Difference : public thrust::binary_function<double, double, double>
{
    __host__ __device__
    double operator()(const double& a, const double& b) const
    {
        return a - b;
    }
};

int main()
{
    std::string filename = "stocks2.csv";

    // Ler os dados do arquivo e armazenar em vetores separados
    std::ifstream input(filename);
    if (!input)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<double> aaplData;
    std::vector<double> msftData;

    std::string line;
    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        double aaplPrice, msftPrice;
        char comma;
        if (iss >> aaplPrice >> comma >> msftPrice)
        {
            aaplData.push_back(aaplPrice);
            msftData.push_back(msftPrice);
        }
    }

    size_t dataSize = aaplData.size(); // Assumindo que os vetores têm o mesmo tamanho

    // Criar os device_vectors a partir dos dados do host
    thrust::device_vector<double> aaplDevice(aaplData.begin(), aaplData.end());
    thrust::device_vector<double> msftDevice(msftData.begin(), msftData.end());

    // Calcular a diferença entre os preços das ações AAPL e MSFT
    thrust::device_vector<double> difference(dataSize);
    thrust::transform(aaplDevice.begin(), aaplDevice.end(), msftDevice.begin(), difference.begin(), Difference());

    // Calcular a média das diferenças
    double sum = thrust::reduce(difference.begin(), difference.end());
    double average = sum / dataSize;

    std::cout << "Average difference between AAPL and MSFT prices: " << average << std::endl;

    // Criar um vetor com todas as componentes iguais à média
    thrust::device_vector<double> averageVector(dataSize, average);

    // Calcular a diferença entre as diferenças e a média
    thrust::device_vector<double> differenceFromAverage(dataSize);
    thrust::transform(difference.begin(), difference.end(), averageVector.begin(), differenceFromAverage.begin(), Difference());

    // Calcular a soma dos quadrados das diferenças em relação à média
    double sumOfSquares = thrust::reduce(differenceFromAverage.begin(), differenceFromAverage.end(), 0.0, thrust::plus<double>());

    // Calcular a variância
    double variance = sumOfSquares / dataSize;

    std::cout << "Variance of differences: " << variance << std::endl;

    return 0;
}
