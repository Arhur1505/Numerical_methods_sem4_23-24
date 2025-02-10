import matplotlib.pyplot as plt

def plot_data(filename, title, ylabel):
    # Wczytywanie danych
    x, y = [], []
    with open(filename, 'r') as file:
        for line in file:
            parts = line.split()
            x.append(float(parts[0]))
            y.append(float(parts[1]))

    # Tworzenie wykresu
    plt.figure(figsize=(6, 6))
    plt.scatter(x, y, alpha=0.5, marker='.')
    plt.title(title)
    plt.xlabel('$x_i$', fontsize = 14)
    plt.ylabel(ylabel, fontsize = 14)
    plt.grid(True)
    plt.axis('equal')
    plt.xlim(0, 1)
    plt.ylim(0, 1)
    plt.savefig(f"{filename}.png")

plot_data('p1i1.txt', 'Wykres par $(x_i, x_{i+1})$ generatora nr 1', '$x_{i+1}$')
plot_data('p1i2.txt', 'Wykres par $(x_i, x_{i+2})$ generatora nr 1', '$x_{i+2}$')
plot_data('p1i3.txt', 'Wykres par $(x_i, x_{i+3})$ generatora nr 1', '$x_{i+3}$')
plot_data('p2i1.txt', 'Wykres par $(x_i, x_{i+1})$ generatora nr 2', '$x_{i+1}$')
plot_data('p2i2.txt', 'Wykres par $(x_i, x_{i+2})$ generatora nr 2', '$x_{i+2}$')
plot_data('p2i3.txt', 'Wykres par $(x_i, x_{i+3})$ generatora nr 2', '$x_{i+3}$')
plot_data('p3i1.txt', 'Wykres par $(x_i, x_{i+1})$ generatora nr 3', '$x_{i+1}$')
plot_data('p3i2.txt', 'Wykres par $(x_i, x_{i+2})$ generatora nr 3', '$x_{i+2}$')
plot_data('p3i3.txt', 'Wykres par $(x_i, x_{i+3})$ generatora nr 3', '$x_{i+3}$')