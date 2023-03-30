#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

using Matriz = vector<vector<double>>;

void calcula_distancias(Matriz &mat, const vector<double> &x, const vector<double> &y) {
    const int n = x.size();
    mat.resize(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            double dist = dx * dx + dy * dy;

            mat[i][j] = dist;
            mat[j][i] = dist;
        }
    }
}

void print_matriz(const Matriz &mat) {
    for (const auto &linha : mat) {
        for (double el : linha) {
            cout << el << " ";
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cin >> n;

    vector<double> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    Matriz mat;
    calcula_distancias(mat, x, y);
    print_matriz(mat);

    return 0;
}
