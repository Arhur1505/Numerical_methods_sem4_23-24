import matplotlib.pyplot as plt
import numpy as np

# Wczytanie danych z pliku
data = np.loadtxt('F2.txt')

# Wyodrębnienie kolumn
column1 = data[:, 0]
column2 = data[:, 1]

# Utworzenie osi X (liczba iteracji)
iterations = np.arange(0, len(column1))

# Utworzenie wykresu
plt.figure(figsize=(10, 6))
plt.plot(iterations, column1, marker='o', label='F[$x_{1},x_{2}$]')
plt.plot(iterations, column2, marker='o', label='F[$x_{1},x_{2},x_{3}$]')
plt.xlabel('Iteracja', fontsize=14)
plt.ylabel('Wartość', fontsize=14)
plt.legend()
plt.xlim(0, 100)  
plt.xticks(np.arange(0, 101, 10))
plt.grid(True)
plt.savefig('wykres.png', format='png', dpi=300)
