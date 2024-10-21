import os
import numpy as np
import matplotlib.pyplot as plt
import glob
from sklearn.model_selection import train_test_split

N1 = 100
N2 = 100
n = 2

def knn(points, p, k=3):
    dist = []
    for group in points:
        for feature in points[group]:
            euclidean_distance = np.linalg.norm(feature - p)
            dist.append((euclidean_distance, group))
    sorted_dist = sorted(dist, key=lambda x: x[0])[:k]
    p1 = sum(1 for d in sorted_dist if d[1] == -1)
    p2 = sum(1 for d in sorted_dist if d[1] == 1)
    return -1 if p1 > p2 else 1



def run(k, sd):
    xc1 = np.random.normal(0, sd, (N1, n)) + np.array([[3, 4]])
    xc2 = np.random.normal(0, sd, (N2, n)) + np.array([[4, 3]])

    points = {
        -1: xc1,
        1: xc2
    }

    plt.scatter(xc1[:, 0], xc1[:, 1], color='blue', label='Classe -1', alpha=0.6)
    plt.scatter(xc2[:, 0], xc2[:, 1], color='red', label='Classe 1', alpha=0.6)

    x_min, x_max = min(min(xc1[:, 0]), min(xc2[:, 0])), max(max(xc1[:, 0]), max(xc2[:, 0]))
    y_min, y_max = min(min(xc1[:, 1]), min(xc2[:, 1])), max(max(xc1[:, 1]), max(xc2[:, 1]))
    xx, yy = np.meshgrid(np.linspace(x_min, x_max, 100), np.linspace(y_min, y_max, 100))
    Z = np.array([knn(points, np.array([x, y]), k=k) for x, y in zip(xx.ravel(), yy.ravel())])
    Z = Z.reshape(xx.shape)

    plt.contourf(xx, yy, Z, alpha=0.3, levels=np.linspace(-1, 1, 3), cmap='coolwarm')
    plt.colorbar()

    plt.xlabel('X1')
    plt.ylabel('X2')
    plt.legend()
    plt.title(f'KNN - k({k}) | sd({sd})')
    plt.savefig(f"images/knn-k{k}-sd{sd}.png")

    plt.close()


directory = "images"

if not os.path.exists(directory):
    os.mkdir(directory)

files = glob.glob(f"{directory}/*")

for f in files:
    os.remove(f)

run(3, 0.3)


""" for sd in range(3, 11, 2):
    run(3, sd/10)

for k, sd in zip(range(3, 11, 2), range(3, 11, 2)):
    run(k, sd/10)
 """