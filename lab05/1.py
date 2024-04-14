import csv
import matplotlib.pyplot as plt

# Wczytanie danych z pliku CSV
alpha_values = []
eigen_values = []

with open("eigen_values_vs_alpha.csv", "r") as file:
    reader = csv.reader(file)
    for row in reader:
        values = row[0].split()  # Podział wiersza na pojedyncze wartości
        alpha_values.append(float(values[0]))
        eigen_values.append([float(val) for val in values[1:]])

# Tworzenie wykresu
plt.figure(figsize=(10, 6))
for i in range(len(eigen_values[0])):
    plt.plot(alpha_values, [val[i] for val in eigen_values], label=f'$\lambda_{i+1}$')

plt.xlabel('Alpha', fontsize=14)
plt.ylabel('Omega', fontsize=14)
plt.title('Wykres 6 kolejnych wartości własnych (ω = √λ = f(α))', fontsize=16)
plt.legend(fontsize=12)
plt.grid(True)

# Ograniczenie osi x do wartości 100 i ustalenie kroków
plt.xlim(0, 100)
plt.xticks(range(0, 101, 10), fontsize=12)

# Ograniczenie osi y do maksymalnej wartości 0.25 i ustalenie kroków
plt.ylim(0, 0.25)
plt.yticks([0.00, 0.05, 0.10, 0.15, 0.20, 0.25], fontsize=12)

# Zapisanie wykresu do pliku PNG
plt.savefig('wykres.png', dpi=300)
plt.show()
