#include <iostream>
#include <fstream>
#include <vector>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>

int main() {
    std::string filename = "stocks.txt";

    std::ifstream input(filename);
    if (!input) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<double> hostData;
    double value;
    while (input >> value) {
        hostData.push_back(value);
    }

    thrust::host_vector<double> hostVector(hostData.begin(), hostData.end());
    thrust::device_vector<double> deviceVector = hostVector;

    // Cálculo do preço médio das ações nos últimos 10 anos
    double avgPriceLast10Years = thrust::reduce(deviceVector.begin(), deviceVector.end()) / deviceVector.size();
    std::cout << "Average price of the last 10 years: " << avgPriceLast10Years << std::endl;

    // Cálculo do preço médio das ações no último ano (365 dias atrás)
    size_t lastYearStartIndex = deviceVector.size() - 365;
    double avgPriceLastYear = thrust::reduce(deviceVector.begin() + lastYearStartIndex, deviceVector.end()) / 365;
    std::cout << "Average price of the last year: " << avgPriceLastYear << std::endl;

    // Cálculo do maior e menor preço da sequência inteira
    auto minMax = thrust::minmax_element(deviceVector.begin(), deviceVector.end());
    double minPrice = *minMax.first;
    double maxPrice = *minMax.second;
    std::cout << "Min price: " << minPrice << std::endl;
    std::cout << "Max price: " << maxPrice << std::endl;

    // Cálculo do maior e menor preço do último ano
    auto lastYearMinMax = thrust::minmax_element(deviceVector.begin() + lastYearStartIndex, deviceVector.end());
    double minPriceLastYear = *lastYearMinMax.first;
    double maxPriceLastYear = *lastYearMinMax.second;
    std::cout << "Min price of the last year: " << minPriceLastYear << std::endl;
    std::cout << "Max price of the last year: " << maxPriceLastYear << std::endl;

    return 0;
}
