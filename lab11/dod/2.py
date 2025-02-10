import matplotlib.pyplot as plt
import numpy as np

def plot_fft_real_imaginary(filename):
    data = np.loadtxt(filename, delimiter=',')
    reals = data[:, 0]
    imags = data[:, 1]

    plt.figure(figsize=(10, 5))
    plt.plot(reals, label='Część rzeczywista', color='b')
    plt.plot(imags, label='Część urojona', color='r', linestyle='-')  # Changed to continuous line
    plt.title('Część rzeczywista i urojona transformaty')
    plt.xlabel('i', fontsize=14)
    plt.ylabel('Wartość', fontsize=14)
    plt.legend()
    plt.grid(True)
    plt.savefig('R_i_u', dpi=300)
    plt.show()

def plot_fft_magnitude(filename):
    data = np.loadtxt(filename, delimiter=',')
    mags = data[:, 2]

    # Calculate discrimination threshold
    max_magnitude = np.max(mags)
    threshold = max_magnitude * 0.5  # Adjust this ratio if needed

    plt.figure(figsize=(10, 5))
    plt.plot(mags, label='Moduł', color='blue')
    plt.axhline(y=threshold, color='r', linestyle='--', label='Próg dyskryminacji')
    plt.title('Wartości modułów współczynników transformaty')
    plt.xlabel('i', fontsize=14)
    plt.ylabel('Moduły', fontsize=14)
    plt.legend()
    plt.grid(True)
    plt.savefig('Mod.png', dpi=300)
    plt.show()

# Adjust the filename path if necessary
plot_fft_real_imaginary('fft_details_k8.txt')
plot_fft_magnitude('fft_details_k8.txt')
