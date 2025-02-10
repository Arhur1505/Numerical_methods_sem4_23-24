import matplotlib.pyplot as plt
import numpy as np

def plot_from_file_with_cos(file_path, output_file):
    with open(file_path, 'r') as file:
        data = [line.strip().split() for line in file]

    x = [float(row[0]) for row in data]
    y = [float(row[1]) for row in data]

    plt.plot(x, y, color='red', label=r'$R_{2,2}$')

    x_cos = np.linspace(-5, 5, 100)
    y_cos = np.cos(x_cos)
    plt.plot(x_cos, y_cos, color='blue', label='cos(x)')

    plt.xlabel('x', fontsize=14)
    plt.ylabel('f(x)', fontsize=14)
    plt.title('N = 6, M = 6', fontsize=14)
    plt.legend()
    plt.grid(True)

    plt.xlim(-5, 5)

    plt.savefig(output_file)
    plt.show()

file_path = 'data.txt' 
output_file = 'wykres.png' 
plot_from_file_with_cos(file_path, output_file)
