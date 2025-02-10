import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import maxwell
import glob

def load_data(filename):
    data = np.loadtxt(filename)
    bin_centers = data[:, 0]
    probabilities = data[:, 1]
    return bin_centers, probabilities

def plot_histogram_with_theoretical_curve(bin_centers, probabilities, sigma, output_file):
    v = np.linspace(0, 5 * sigma, 500)
    theoretical_curve = maxwell.pdf(v, scale=sigma)

    plt.figure()
    plt.bar(bin_centers, probabilities, width=(bin_centers[1] - bin_centers[0]), alpha=0.6, label='Empiryczna')
    
    plt.plot(v, theoretical_curve, 'r-', lw=2, label='Teoretyczna')
    
    plt.xlabel('V[m]', fontsize=10)
    plt.ylabel('Prawdopodobieństwo', fontsize=10)
    plt.title(output_file)
    plt.legend()
    plt.grid(True)
    
    plt.savefig(output_file)
    plt.close()

k = 1.38e-23  
u = 1.66e-27  
T = 100      
m = 40 * u  
sigma = np.sqrt(k * T / m)

histogram_filenames = glob.glob("histogram_*.txt")

for histogram_filename in histogram_filenames:

    bin_centers, probabilities = load_data(histogram_filename)

    output_plot = histogram_filename.replace(".txt", ".png")

    plot_histogram_with_theoretical_curve(bin_centers, probabilities, sigma, output_plot)
