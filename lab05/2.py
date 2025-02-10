import csv
import matplotlib.pyplot as plt
import numpy as np

# Wczytanie danych z pliku CSV
data = []
with open('eigen_vectors_alpha_0.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        data.append([float(val) for val in row[0].split()])  # Split na poszczególne wartości

# Utworzenie nowego obiektu figury i osi
fig, ax = plt.subplots()

# Narysowanie danych dla każdej kolumny
for i, column in enumerate(zip(*data)):
    ax.plot(column, label=f'u{i+1}')

# Dodanie siatki na wykresie
ax.grid(True)

# Dodanie legendy z indeksami kolumn
legend_labels = [f'u{i+1}' for i in range(len(data))]
ax.legend(legend_labels)

# Ustawienie zakresów osi x i y
ax.set_xlim(-5, 5)
ax.set_ylim(-0.1, 0.1)

# Przekształcenie ticków na osi x
ticks = np.linspace(0, 200, 11)  # Punkty od 0 do 200, z krokiem co 20
tick_labels = np.linspace(-5, 5, len(ticks))  # Odpowiadające im etykiety
ax.set_xticks(ticks)
ax.set_xticklabels([f'{label:.0f}' for label in tick_labels])  # Formatowanie etykiet

# Dodanie tytułu i etykiet osi
ax.set_title('Wykres wektorów własnych dla alfa = 0')
ax.set_xlabel('x')
ax.set_ylabel('u(x)')

# Zapisanie wykresu do pliku PNG
plt.savefig('wykres0.png', dpi=300)

# Wyświetlenie wykresu
plt.show()