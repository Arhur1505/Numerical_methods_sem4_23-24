import numpy as np
import matplotlib.pyplot as plt

# Definicja funkcji
def f(x):
    return x**4 - 7.899*x**3 + 23.281114*x**2 + 14.73866033 - 30.33468152*x

# Zakres dla wartości x
x = np.linspace(1.5, 2.4, 400)

# Obliczenie wartości y dla każdego x
y = f(x)

# Generowanie wykresu
plt.figure(figsize=(10, 6))
plt.plot(x, y, label='f(x)')
plt.title('Wykres funkcji f(x)')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.axhline(0, color='black', lw=0.5) # Linia y=0 dla odniesienia
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()

# Wyświetlenie wykresu
plt.show()
plt.savefig('plot.png', format='png', dpi=300)