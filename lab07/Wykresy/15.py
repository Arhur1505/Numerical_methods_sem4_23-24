import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

plik_sciezka1 = 'interpolacja_n15_row.txt'
plik_sciezka2 = 'interpolacja_n15_czeb.txt'

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

xcz = [7.97352, 7.76317, 7.35057, 6.75156, 5.98916, 5.09268, 4.09657, 3.03909, 1.96091, 0.903434, -0.0926821, -0.989163, -1.75156, -2.35057, -2.76317, -2.97352]
ycz = [f(i) for i in xcz]

xr = [-3, -2.26667, -1.53333, -0.8, -0.0666667, 0.666667, 1.4, 2.13333, 2.86667, 3.6, 4.33333, 5.06667, 5.8, 6.53333, 7.26667, 8]
yr = [f(i) for i in xr]

plt.plot(x, f(x), 'black', label='Funkcja interpolowana')

wczytaj_i_interpoluj(plik_sciezka1, 'red', 'Interpolacja równomierna')
wczytaj_i_interpoluj(plik_sciezka2, 'blue', 'Interpolacja Czybyszewa')

plt.plot(xr, yr, 'o', color='red', label='Węzły funkcji')  
plt.plot(xcz, ycz, 'o', color='blue', label='Węzły funkcji') 

plt.legend()
plt.xlabel('x', fontsize=12)
plt.ylabel('f(x)', fontsize=12)
plt.grid(True)
plt.title('n = 15')
plt.xlim(-3, 8) 


plt.savefig('n=15.png', format='png', dpi=600)