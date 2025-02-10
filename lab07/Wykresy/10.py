import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

plik_sciezka1 = 'interpolacja_n10_row.txt'
plik_sciezka2 = 'interpolacja_n10_czeb.txt'

def wczytaj_i_interpoluj(plik_sciezka, kolor_krzywej, etykieta):
    x = []
    y = []

    with open(plik_sciezka, 'r') as plik:
        for linia in plik:
            wartosci = linia.split() 
            x.append(float(wartosci[0]))
            y.append(float(wartosci[1]))

    x = np.array(x)
    y = np.array(y)

    f = interp1d(x, y, kind='cubic')
    x_nowe = np.linspace(min(x), max(x), num=500, endpoint=True)
    plt.plot(x_nowe, f(x_nowe), '-', color=kolor_krzywej, label=etykieta)

def f(x):
    return x / (1 + x**2)

x = np.linspace(-3, 8, 100)

xcz = [7.94402, 7.50298, 6.65662, 5.47352, 4.04953, 2.5, 0.950471, -0.473524, -1.65662, -2.50298, -2.94402]
ycz = [f(i) for i in xcz]

xr = [-3, -1.9, -0.8, 0.3, 1.4, 2.5, 3.6, 4.7, 5.8, 6.9, 8]
yr = [f(i) for i in xr]

plt.plot(x, f(x), 'black', label='Funkcja interpolowana')

wczytaj_i_interpoluj(plik_sciezka1, 'red', 'Interpolacja równomierna')
wczytaj_i_interpoluj(plik_sciezka2, 'blue', 'Interpolacja Czybyszewa')

plt.plot(xr, yr, 'ro', label='Węzły funkcji')  
plt.plot(xcz, ycz, 'bo', label='Węzły funkcji') 

plt.legend()
plt.xlabel('x', fontsize=12)
plt.ylabel('f(x)', fontsize=12)
plt.grid(True)
plt.xlim(-3, 8) 
plt.title('n = 10')
plt.savefig('n=10.png', format='png', dpi=600)