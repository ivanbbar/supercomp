#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;

int SEED = 10;
default_random_engine generator(SEED);
uniform_real_distribution<double> distribution(0.0, 1.0);
double getProbability() {
return distribution(generator);
}

struct Objeto {
int id;
int valor;
int peso;
bool selecionado;
};

bool comparaobjetosValor(Objeto a, Objeto b) {
return a.valor > b.valor;
}

bool comparaobjetosPeso(Objeto a, Objeto b) {
return a.peso < b.peso;
}

int main() {
    int N, W;
    cin >> N >> W;
    Objeto objetos[N];
    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        cin >> objetos[i].peso >> objetos[i].valor;
        objetos[i].selecionado = false;
    }

    sort(objetos, objetos + N, comparaobjetosValor);

    int peso = 0;
    int valor = 0;
    int resposta[N] = {0};
    int T = 0;

    for (int i = 0; i < N; i++) {
        if (peso + objetos[i].peso <= W) {
            resposta[T] = objetos[i].id;
            peso += objetos[i].peso;
            valor += objetos[i].valor;
            objetos[i].selecionado = true;
            T++;
        }
    }

    cout << peso << " " << valor << " ";

    // Verifica se a solução encontrada é ótima global
    int capacidade_restante = W - peso;
    bool encontrou_melhoria = true;
    while (encontrou_melhoria) {
        encontrou_melhoria = false;
        for (int i = 0; i < N; i++) {
            if (!objetos[i].selecionado) {
                double prob = getProbability();
                if (prob <= 0.25) {
                    resposta[T] = objetos[i].id;
                    peso += objetos[i].peso;
                    valor += objetos[i].valor;
                    objetos[i].selecionado = true;
                    T++;
                } else if (peso + objetos[i].peso <= W) {
                    resposta[T] = objetos[i].id;
                    peso += objetos[i].peso;
                    valor += objetos[i].valor;
                    objetos[i].selecionado = true;
                    T++;
                }
                if (peso == W) {
                    break;
                }
            }
        }
    }

    if (peso == W) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }

    sort(resposta, resposta + T);

    for (int i = 0; i < T; i++) {
        cout << resposta[i] << " ";
    }

    cout << endl;

    return 0;
}