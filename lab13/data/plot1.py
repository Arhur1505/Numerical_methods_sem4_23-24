import matplotlib.pyplot as plt

def read_errors(filename):
    with open(filename, 'r') as file:
        errors = [float(line.strip()) for line in file]
    return errors

def plot_errors(errors, title, xlabel, ylabel, file_output):
    n_values = range(2, 2 + len(errors))  # Zakładamy, że n zaczyna się od 2
    plt.figure()
    plt.plot(n_values, errors, marker='o')
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.savefig(file_output)
    plt.show()

# Odczytanie błędów z plików
errors1 = read_errors('errors1.txt')
errors2_k5 = read_errors('errors2_k5.txt')
errors2_k10 = read_errors('errors2_k10.txt')
errors3 = read_errors('errors3.txt')

# Tworzenie wykresów
plot_errors(errors1, 'Błędy całki pierwszej', 'Liczba węzłów n', 'Błąd bezwzględny', 'errors1.png')
plot_errors(errors2_k5, 'Błędy całki drugiej dla k=5', 'Liczba węzłów n', 'Błąd bezwzględny', 'errors2_k5.png')
plot_errors(errors2_k10, 'Błędy całki drugiej dla k=10', 'Liczba węzłów n', 'Błąd bezwzględny', 'errors2_k10.png')
plot_errors(errors3, 'Błędy podwójnej całki', 'Liczba węzłów n', 'Błąd bezwzględny', 'errors3.png')