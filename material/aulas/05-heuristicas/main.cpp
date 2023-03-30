#include <iostream>
#include <algorithm>
using namespace std;

struct Objeto {
    int id;
    int valor;
    int peso;
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
    }

    sort(objetos, objetos + N, comparaobjetosPeso);

    int peso = 0;
    int valor = 0;
    int resposta[N] = {0};
    int T = 0;

    for (int i = 0; i < N; i++) {
        if (peso + objetos[i].peso <= W) {
            resposta[T] = objetos[i].id;
            peso += objetos[i].peso;
            valor += objetos[i].valor;
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
            if (peso + objetos[i].peso <= W && objetos[i].valor > objetos[resposta[T-1]].valor) {
                encontrou_melhoria = true;
                peso += objetos[i].peso - objetos[resposta[T-1]].peso;
                valor += objetos[i].valor - objetos[resposta[T-1]].valor;
                resposta[T-1] = objetos[i].id;
                sort(resposta, resposta + T);
                break;
            }
        }
    }

    if (peso == W) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }

    for (int i = 0; i < T; i++) {
        cout << resposta[i] << " ";
    }

    cout << endl;

    return 0;
}