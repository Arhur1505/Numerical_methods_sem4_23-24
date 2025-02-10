import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

plik_sciezka1 = 'interpolacja_n5_row.txt'
plik_sciezka2 = 'interpolacja_n5_czeb.txt'

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

xcz = [7.81259, 6.38909, 3.9235, 1.0765, -1.38909, -2.81259]
ycz = [f(i) for i in xcz]

xr = [-3, -0.8, 1.4, 3.6, 5.8, 8]
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
plt.title('n = 5')
plt.savefig('n=5.png', format='png', dpi=600)