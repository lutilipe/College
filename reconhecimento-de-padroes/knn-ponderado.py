import os
import numpy as np
import matplotlib.pyplot as plt
import glob
import math

N1 = 100
N2 = 100
n = 2

def knn(points, p, h=2, k=3):
    dist = []
    for group in points:
        for feature in points[group]:
            euclidean_distance = np.linalg.norm(feature - p)
            dist.append((math.exp(-(euclidean_distance / (h * h))), group))
    
    sorted_dist = sorted(dist, key=lambda x: x[0], reverse=True)[:k]

    q1 = sum(d[0] for d in sorted_dist if d[1] == 1)
    q2 = sum(d[0] for d in sorted_dist if d[1] == -1)

    return -1 if q2 > q1 else 1

def generate_spiral_points(n_points, noise=0.5):
    n = n_points // 2
    
    theta = np.sqrt(np.random.rand(n)) * 2 * np.pi
    
    r_a = 2 * theta + np.pi
    r_b = -2 * theta - np.pi

    class_a_x = r_a * np.cos(theta) + np.random.randn(n) * noise
    class_a_y = r_a * np.sin(theta) + np.random.randn(n) * noise
    class_b_x = r_b * np.cos(theta) + np.random.randn(n) * noise
    class_b_y = r_b * np.sin(theta) + np.random.randn(n) * noise
    
    class_a = np.vstack((class_a_x, class_a_y)).T
    class_b = np.vstack((class_b_x, class_b_y)).T
    X = np.vstack((class_a, class_b))
    y = np.hstack((np.ones(n), -np.ones(n)))
    
    return X, y

def run2(k, sd, h):
    X, y = generate_spiral_points(n_points=200, noise=0.6)

    xc1 = X[y == -1]
    xc2 = X[y == 1]

    points = {
        -1: xc1,
        1: xc2,
    }

    """ plt.scatter(xc1[:, 0], xc1[:, 1], color='blue', label='Classe -1', alpha=0.6)
    plt.scatter(xc2[:, 0], xc2[:, 1], color='red', label='Classe 1', alpha=0.6)
    plt.scatter(3.5, 3.5, color='green', label='Classe TEste', alpha=0.6) """


    plt.scatter(xc1[:, 0], xc1[:, 1], color='blue', label='Classe -1', alpha=0.6)
    plt.scatter(xc2[:, 0], xc2[:, 1], color='red', label='Classe 1', alpha=0.6)

    x_min, x_max = min(min(xc1[:, 0]), min(xc2[:, 0])), max(max(xc1[:, 0]), max(xc2[:, 0]))
    y_min, y_max = min(min(xc1[:, 1]), min(xc2[:, 1])), max(max(xc1[:, 1]), max(xc2[:, 1]))
    xx, yy = np.meshgrid(np.linspace(x_min, x_max, 100), np.linspace(y_min, y_max, 100))
    Z = np.array([knn(points, np.array([x, y]), k=k, h=h) for x, y in zip(xx.ravel(), yy.ravel())])
    Z = Z.reshape(xx.shape)

    plt.contourf(xx, yy, Z, alpha=0.3, levels=np.linspace(-1, 1, 3), cmap='coolwarm')
    plt.colorbar()

    plt.xlabel('X1')
    plt.ylabel('X2')
    plt.legend()
    #plt.savefig(f"images/knn-k{k}-sd{sd}.png")
    plt.show()

    plt.close()

def run(k, sd, h):
    xc1 = np.random.normal(0, sd, (N1, n)) + np.array([[3, 4]])
    xc2 = np.random.normal(0, sd, (N2, n)) + np.array([[4, 3]])

    points = {
        -1: xc1,
        1: xc2
    }

    """ plt.scatter(xc1[:, 0], xc1[:, 1], color='blue', label='Classe -1', alpha=0.6)
    plt.scatter(xc2[:, 0], xc2[:, 1], color='red', label='Classe 1', alpha=0.6)
    plt.scatter(3.5, 3.5, color='green', label='Classe TEste', alpha=0.6) """


    plt.scatter(xc1[:, 0], xc1[:, 1], color='blue', label='Classe -1', alpha=0.6)
    plt.scatter(xc2[:, 0], xc2[:, 1], color='red', label='Classe 1', alpha=0.6)

    x_min, x_max = min(min(xc1[:, 0]), min(xc2[:, 0])), max(max(xc1[:, 0]), max(xc2[:, 0]))
    y_min, y_max = min(min(xc1[:, 1]), min(xc2[:, 1])), max(max(xc1[:, 1]), max(xc2[:, 1]))
    xx, yy = np.meshgrid(np.linspace(x_min, x_max, 100), np.linspace(y_min, y_max, 100))
    Z = np.array([knn(points, np.array([x, y]), k=k, h=h) for x, y in zip(xx.ravel(), yy.ravel())])
    Z = Z.reshape(xx.shape)

    plt.contourf(xx, yy, Z, alpha=0.3, levels=np.linspace(-1, 1, 3), cmap='coolwarm')
    plt.colorbar()

    plt.xlabel('X1')
    plt.ylabel('X2')
    plt.legend()
    plt.title(f'KNN - k({k}) | sd({sd})')
    #plt.savefig(f"images/knn-k{k}-sd{sd}.png")
    plt.show()

    plt.close()


directory = "images"

if not os.path.exists(directory):
    os.mkdir(directory)

files = glob.glob(f"{directory}/*")

for f in files:
    os.remove(f)

#run(k=16, sd=0.6, h=2)
run2(k=45, sd=0.6, h=2)
