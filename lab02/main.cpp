#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    float xb = 2;
    float xa = 0.5;
    float n = 500;
    float h = 2 * xb / (n - 1);

    float d = -2 / (h * h);
    float a = 1 / (h * h);
    float c = a;

    float tabA[500];
    float tabD[500];
    float tabC[500];
    float p[500];
    float tabX[500];

    for (int i = 0; i < 500; i++)
    {
        tabA[i] = a;           // A
        tabD[i] = d;           // D
        tabC[i] = c;           // C
        tabX[i] = -xb + h * i; // X
    }
    tabA[0] = 0;
    tabA[499] = 0;
    tabD[0] = 1;
    tabD[499] = 1;
    tabC[0] = 1;

    // p
    for (int i = 0; i < 500; i++)
    {
        if (tabX[i] >= -xb && tabX[i] < -xa)
        {
            p[i] = 0;
        }
        else if (tabX[i] >= -xa && tabX[i] < 0)
        {
            p[i] = 1;
        }
        else if (tabX[i] == 0)
        {
            p[i] = 0;
        }
        else if (tabX[i] > 0 && tabX[i] <= xa)
        {
            p[i] = -1;
        }
        else if (tabX[i] > xa && tabX[i] <= xb)
        {
            p[i] = 0;
        }
    }

    float tabU[500];
    float tabL[500];

    tabU[0] = tabD[0];
    for (int i = 1; i < 500; i++)
    {
        tabL[i] = tabA[i] / tabU[i - 1];
        tabU[i] = tabD[i] - tabL[i] * tabC[i - 1];
    }

    float tabY[500];

    tabY[0] = -p[0];
    for (int i = 1; i < 500; i++)
    {
        tabY[i] = -p[i] - tabL[i] * tabY[i - 1];
    }

    float tabV[500];

    for (int i = 0; i < 500; i++)
    {
        if (tabX[i] >= -xa && tabX[i] <= -xb)
        {
            tabV[i] = tabX[i] / 16 + 1 / 8;
        }
        if (tabX[i] >= -xa && tabX[i] <= 0)
        {
            tabV[i] = -tabX[i] * tabX[i] / 2 - 7 / 16 * tabX[i];
        }
        if (tabX[i] >= 0 && tabX[i] <= xa)
        {
            tabV[i] = tabX[i] * tabX[i] / 2 - 7 / 16 * tabX[i];
        }
        if (tabX[i] >= xa && tabX[i] <= xb)
        {
            tabV[i] = tabX[i] / 16 - 1 / 8;
        }
    }

    // Zapisywanie danych do plików
    ofstream plik("wyniki.txt");
    if (plik.is_open())
    {
        for (int i = 0; i < 500; i++)
        {
            plik << tabX[i] << ", " << tabV[i] << "\n";
        }
        plik.close();
        cout << "Wyniki zapisano do pliku 'wyniki.txt'" << endl;
    }
    else
    {
        cerr << "Błąd przy otwieraniu pliku do zapisu." << endl;
    }

    return 0;
}