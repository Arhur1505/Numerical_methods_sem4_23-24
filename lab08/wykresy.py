import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

SAVE = True

for i in [5, 6, 10, 20]:
    df = pd.read_csv('interpolation_results_{}.txt'.format(i), sep=' ')
    nodes = pd.read_csv('nodes_xi_{}.txt'.format(i), sep=' ')

    x = df["x"]
    y = df["y"]

    plt.figure()  
    plt.plot(x, 1/(1+x**2), label='Funkcja interpolowana', color='blue')
    plt.plot(x, y, label='Interpolacja funkcjami sklejanymi', color='red')
    plt.scatter(nodes["x"], nodes["y"], label='Węzły', color='red', marker='o')
    plt.scatter(nodes["x"], 1/(1+nodes["x"]**2), color='red', marker='o')
    plt.xlabel('x', fontsize=14)
    plt.ylabel('f(x)', fontsize=14)
    plt.title('n = {}'.format(i))
    plt.legend()
    plt.grid(True)
    plt.xlim(-5, 5)  # Ustawienie przedziału osi X

    if SAVE:
        plt.savefig('interpolation_plot_n_{}.png'.format(i))
    plt.close()

for i in [6, 7, 14]:
    df = pd.read_csv('interpolation_results_{}f_2.txt'.format(i), sep=' ')
    nodes = pd.read_csv('nodes_xi_{}f_2.txt'.format(i), sep=' ')

    x = df["x"]
    y = df["y"]

    plt.figure()  
    plt.plot(x, np.cos(2*x), label='Funkcja interpolowana', color='blue')
    plt.plot(x, y, label='Interpolacja funkcjami sklejanymi', color='red')
    plt.scatter(nodes["x"], nodes["y"], label='Węzły', color='red', marker='o')
    plt.xlabel('x', fontsize=14)
    plt.ylabel('f(x)', fontsize=14)
    plt.title('n = {}'.format(i))
    plt.legend()
    plt.grid(True)
    plt.xlim(-5, 5)  # Ustawienie przedziału osi X

    if SAVE:
        plt.savefig('interpolation_plot_n_{}_f_2.png'.format(i))
    plt.close()