import numpy as np
import matplotlib.pyplot as plt

def read_data(filename):
    with open(filename, 'r') as file:
        data = np.array([float(line.strip()) for line in file])
    return data

def plot_signal_with_noise(clean_data, noisy_data, title, filename):
    plt.figure(figsize=(10, 6))
    plt.plot(clean_data, label='Odfiltrowany', color='blue')
    noise_points = noisy_data - clean_data
    noise_indices = np.where(noise_points != 0)[0]
    plt.scatter(noise_indices, noisy_data[noise_indices], color='red', label='Zaburzony', s=10)
    plt.title(title)
    plt.xlabel('i', fontsize=14)
    plt.ylabel('y(i)', fontsize=14)
    plt.legend()
    plt.grid(True)
    plt.savefig(filename, dpi=300)

def plot_signal_with_filtered(clean_data, filtered_data, title, filename):
    plt.figure(figsize=(10, 6))
    plt.plot(clean_data, label='Niezaburzony', color='blue')
    plt.plot(filtered_data, label='Odszumiony', color='red', linestyle='--')
    plt.title(title)
    plt.xlabel('i', fontsize=14)
    plt.ylabel('y(i)', fontsize=14)
    plt.legend()
    plt.grid(True)
    plt.savefig(filename, dpi=300)

k_values = [8, 10, 12]

for k in k_values:
    N = 1 << k

    clean_signal = read_data(f'clean_signal_k{k}.txt')
    filtered_noisy_signal = read_data(f'filtered_noisy_signal_k{k}.txt')
    noisy_signal = read_data(f'noisy_signal_k{k}.txt')

    plot_signal_with_noise(filtered_noisy_signal, noisy_signal, f'Sygnał zaburzony i odszumiony (k={k})', f'zab_i_od_k{k}.png')
    plot_signal_with_filtered(clean_signal, filtered_noisy_signal, f'Sygnał niezaburzony i odszumiony (k={k})', f'niezab_i_od_k{k}.png')