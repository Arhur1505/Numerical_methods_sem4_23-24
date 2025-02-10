import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def plot_3d_vectors(filename_sphere, filename_ball, save_plots=False, show_plots=True):
    x_sphere, y_sphere, z_sphere = [], [], []
    x_ball, y_ball, z_ball = [], [], []

    # Wczytywanie danych z pliku dla punktów na sferze
    with open(filename_sphere, 'r') as file:
        for line in file:
            parts = line.strip().split()
            x_sphere.append(float(parts[0]))
            y_sphere.append(float(parts[1]))
            z_sphere.append(float(parts[2]))

    # Wczytywanie danych z pliku dla punktów w kuli
    with open(filename_ball, 'r') as file:
        for line in file:
            parts = line.strip().split()
            x_ball.append(float(parts[0]))
            y_ball.append(float(parts[1]))
            z_ball.append(float(parts[2]))

    # Tworzenie wykresu 3D dla punktów na sferze
    fig_sphere = plt.figure(figsize=(10, 7))
    ax_sphere = fig_sphere.add_subplot(111, projection='3d')
    scatter_sphere = ax_sphere.scatter(x_sphere, y_sphere, z_sphere, c='r', marker='o', s=4, alpha=0.7)
    ax_sphere.set_xlabel('x')
    ax_sphere.set_ylabel('y')
    ax_sphere.set_zlabel('z')
    ax_sphere.set_title('Rozkład punktów na sferze')
    ax_sphere.grid(True)
    ax_sphere.set_xlim(-1, 1)
    ax_sphere.set_ylim(-1, 1)
    ax_sphere.set_zlim(-1, 1)

    if save_plots:
        fig_sphere.savefig('sphere_plot.png', dpi=300, bbox_inches='tight')

    # Tworzenie wykresu 3D dla punktów w kuli
    fig_ball = plt.figure(figsize=(10, 7))
    ax_ball = fig_ball.add_subplot(111, projection='3d')
    scatter_ball = ax_ball.scatter(x_ball, y_ball, z_ball, c='b', marker='o', s=4, alpha=0.7)
    ax_ball.set_xlabel('x')
    ax_ball.set_ylabel('y')
    ax_ball.set_zlabel('z')
    ax_ball.set_title('Rozkład punktów w kuli')
    ax_ball.grid(True)
    ax_ball.set_xlim(-1, 1)
    ax_ball.set_ylim(-1, 1)
    ax_ball.set_zlim(-1, 1)

    if save_plots:
        fig_ball.savefig('ball_plot.png', dpi=300, bbox_inches='tight')

    if show_plots:
        plt.show()

# Ścieżki do plików zawierających wektory
file_path_sphere = 'normalized_vectors_on_sphere.txt'
file_path_ball = 'points_inside_ball.txt'

# Wywołanie funkcji z odpowiednimi ścieżkami
plot_3d_vectors(file_path_sphere, file_path_ball, save_plots=True, show_plots=True)