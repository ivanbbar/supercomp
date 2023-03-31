#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct Item {
    int id;
    double peso;
    double valor;
};

double GetProbability() {
    static default_random_engine generator(time(nullptr));
    static uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

void SortByValue(vector<Item>& itens) {
    sort(itens.begin(), itens.end(), [](const Item& a, const Item& b) {
        return a.valor > b.valor;
    });
}

void SortByWeight(vector<Item>& itens) {
    sort(itens.begin(), itens.end(), [](const Item& a, const Item& b) {
        return a.peso < b.peso;
    });
}

void ReadInputItems(vector<Item>& destiny, int n_total) {
    double w, v;
    for (int i = 0; i < n_total; i++) {
        cin >> w >> v;
        destiny.push_back({i, w, v});
    }
}

double CalculateFitting(const vector<Item>& itens, const vector<int>& ids_selecionados) {
    double valor = 0;
    for (size_t i = 0; i < itens.size(); i++) {
        if (ids_selecionados[i] == 1) {
            valor += itens[i].valor;
        }
    }
    return valor;
}

void GenerateRandomKnapsack(const vector<Item>& itens, vector<int>& ids_selecionados, double capacidade) {
    ids_selecionados.clear();
    double peso = 0;
    for (const auto& item : itens) {
        double prob = GetProbability();
        if (prob < 0.5) {
            if (peso + item.peso <= capacidade) {
                peso += item.peso;
                ids_selecionados.push_back(1);
            } else {
                ids_selecionados.push_back(0);
            }
        } else {
            ids_selecionados.push_back(0);
        }
    }
}

int main() {
    int n_total;
    double capacidade;
    cin >> n_total >> capacidade;

    vector<Item> itens;
    ReadInputItems(itens, n_total);

    vector<vector<int>> mochilas_geradas;
    vector<double> valores;

    for (int i = 0; i < 10; i++) {
        vector<int> ids_selecionados;
        GenerateRandomKnapsack(itens, ids_selecionados, capacidade);
        mochilas_geradas.push_back(ids_selecionados);
        double valor_total = CalculateFitting(itens, ids_selecionados);
        valores.push_back(valor_total);
    }

    auto it = max_element(valores.begin(), valores.end());
    int idx_melhor_mochila = distance(valores.begin(), it);

    cout << "Melhor mochila: " << valores[idx_melhor_mochila] << endl;

    return 0;
}
