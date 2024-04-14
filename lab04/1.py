import matplotlib.pyplot as plt

# Dane
data = {
    1: [0.000548461, 0.282512, 0.284531, 0.284903, 0.284972, 0.284985, 0.284987, 0.284988, 0.284988, 0.284988, 0.284988, 0.284988],
    2: [1.91485e-05, 0.121709, 0.122242, 0.122514, 0.12265, 0.122719, 0.122753, 0.12277, 0.122778, 0.122782, 0.122784, 0.122785],
    3: [7.64792e-07, 0.0865954, 0.0865954, 0.0865955, 0.0865995, 0.0867844, 0.0952313, 0.312156, 0.577366, 0.590103, 0.590384, 0.59039],
    4: [7.64792e-07, 0.0865955, 0.0865955, 0.0865955, 0.0865955, 0.0865955, 0.0865955, 0.0865955, 0.0865955, 0.0865955, 0.0865955, 0.0865955],
    5: [4.55772e-11, 3.06401e-07, 0.170944, 0.170974, 0.170974, 0.170974, 0.170974, 0.170974, 0.170974, 0.170974, 0.170974, 0.170974],
    6: [4.55772e-11, 3.03351e-07, 1.50615e-06, 0.0981543, 0.0981544, 0.0981544, 0.0981544, 0.0981544, 0.0981544, 0.0981544, 0.0981544, 0.0981544]
}

# Tworzenie wykresu punktowego
colors = ['orange', 'green', 'red', 'purple', 'brown', 'pink']
for k, values in data.items():
    plt.scatter(range(len(values)), values, label=f'k={k}', s=20, c=colors[k-1], zorder=2)  # Ustawienie rozmiaru kropek na 20 i koloru

# Konfiguracja wykresu
plt.xlabel('i')
plt.ylabel('Wartość')
plt.title('Wartości własne')
plt.legend()
plt.grid(True)

# Ustawienie białego tła
plt.gca().set_facecolor('white')

# Zapisanie wykresu do pliku PNG bez łączenia punktów
plt.savefig('scatter_plot.png', bbox_inches='tight', dpi=300)

# Wyświetlenie wykresu
plt.show()