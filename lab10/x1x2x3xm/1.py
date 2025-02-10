import matplotlib.pyplot as plt
import numpy as np

# Wczytanie danych z pliku
data = np.loadtxt('f2.txt')

# Wyodrębnienie kolumn
x1 = data[:, 0]
x2 = data[:, 1]
x3 = data[:, 2]
xm = data[:, 3]

# Utworzenie osi X (liczba iteracji)
iterations = np.arange(0, len(x1))

# Utworzenie wykresu
plt.figure(figsize=(10, 6))
plt.plot(iterations, x1, marker='o', label='$x_{1}$')
plt.plot(iterations, x2, marker='o', label='$x_{2}$')
plt.plot(iterations, x3, marker='o', label='$x_{3}$')
plt.plot(iterations, xm, marker='o', label='$x_{m}$')
plt.xlabel('Iteracja', fontsize=14)
plt.ylabel('Wartość', fontsize=14)
plt.legend()
plt.xticks(np.arange(0, 101, 10))
plt.xlim(0, 100)
plt.grid(True)
plt.savefig('wykres.png', format='png', dpi=300)
