import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Funkcja pierwsza
x = np.linspace(0, 2, 400)
y1 = x / (4 * x**2 + 1)
plt.figure(figsize=(6, 4))
plt.plot(x, y1, label=r'$f_1$')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.savefig('f1.png', dpi = 300)
plt.close()

# Funkcja druga dla k=5
k = 5
x = np.linspace(0, 25, 400)
y2 = x**k * np.exp(-x)
plt.figure(figsize=(6, 4))
plt.plot(x, y2, label=r'$f_2}$')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.savefig('f25.png', dpi = 300)
plt.close()

# Funkcja druga dla k=10
k = 10
x = np.linspace(0, 25, 400)
y3 = x**k * np.exp(-x)
plt.figure(figsize=(6, 4))
plt.plot(x, y3, label=r'$f_2$')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.savefig('f210.png', dpi = 300)
plt.close()

# Funkcja trzecia, dwuwymiarowa
x = np.linspace(-3, 3, 400)
y = np.linspace(-3, 3, 400)
X, Y = np.meshgrid(x, y)
Z = np.sin(X)**2 * np.sin(Y)**4 * np.exp(-X**2 - Y**2)

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, Z, cmap='viridis')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
plt.savefig('f3.png', dpi = 300)
plt.close()