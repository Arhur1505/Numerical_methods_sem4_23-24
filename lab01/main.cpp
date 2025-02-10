#include <iostream>

using namespace std;

int main() {
    int i, j, k, n;
    
    n = 3;

    float mat[3][4] = {
        {-1, 2, 1, -1},
        {1, -3, -2, -1},
        {3, -1, -1, 4}
    };

    float wynik[n];

    for(i = 0; i < n-1; i++) {
        for(j = i + 1; j < n; j++) {
            float f = mat[j][i] / mat[i][i];

            for(k = 0; k < n+1; k++) {
                mat[j][k] = mat[j][k] - f * mat[i][k];
            }    
        }
    }

    for(i = n-1; i >= 0; i--) {
        wynik[i] = mat[i][n];
        for(j = i+1; j < n; j++) {
            if(i != j) {
                wynik[i] = wynik[i] - mat[i][j] * wynik[j];
            }
        }
        wynik[i] = wynik[i] / mat[i][i];
    }

    for (i = 0; i < n; i++) {
        cout << wynik[i] << ", ";
    }
    cout << endl;

    return 0;
}