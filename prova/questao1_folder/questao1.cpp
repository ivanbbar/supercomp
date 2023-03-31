#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <bitset>
#include <cmath>

using namespace std;

double distance(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371000;
    double phi1 = lat1 * M_PI / 180;
    double phi2 = lat2 * M_PI / 180;
    double dphi = (lat2 - lat1) * M_PI / 180;
    double dlambda = (lon2 - lon1) * M_PI / 180;
    double a = pow(sin(dphi / 2), 2) + cos(phi1) * cos(phi2) * pow(sin(dlambda / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance;
    }

int main() {
    int n;
    cin >> n;

    // trabalhar com todos os inputs numa estrutura so 
    vector < pair<double, double>> atividades(n);
    for (int i = 0; i < n; i++) {
        double latitude, longitude;
        cin >> latitude >> longitude;
        atividades[i] = {latitude, longitude};
    }

    // inicia logica de ordenacao e visitas
    vector<int> sequencia(n);
    sequencia[0] = 0;
    // cria vetor de visitas e joga todo mundo pra false
    vector<bool> javisitei(n, false);
    // mas, o primeiro tem que ser true (Escolha uma atividade inicial aleat ́oria e adicione `a lista de atividades a serem visitadas)
    javisitei[0] = true;
    double distancia_percorrida = 0;

// Para cada atividade n ̃ao visitada, calcule a distˆancia (ou tempo) para a atividade atualmente selecionada.
    for (int i = 0; i < n; i++) {
        // inicia distancia_mais_perto com o maximo possivel
        double distancia_mais_perto = std::numeric_limits<double>::max();            
        int mais_perto = 0;                        
        for (int j = 0; j < n; j++) {
            int pos_select = sequencia[i-1];             
            if (!javisitei[j]) {
                double distancia = distance(atividades[pos_select].first, atividades[pos_select].second,atividades[j].first, atividades[j].second);
                if (distancia < distancia_mais_perto) {
                    distancia_mais_perto = distancia;
                    mais_perto = j;
                }
            }
        }
        sequencia[i] = mais_perto;
        javisitei[mais_perto] = true;
        distancia_percorrida += distancia_mais_perto;

        }

    cout << "Distância total percorrida: " << distancia_percorrida << "metros" << endl;
    cout << "Ordem das atividades: " << endl;

    for (int i = 0; i < n; i++) {
        cout << sequencia[i-1] +1 << endl;
    }
    return 0;
}

