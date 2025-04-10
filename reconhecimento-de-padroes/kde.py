import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.spatial.distance import cdist
from scipy.spatial.distance import pdist, squareform

def dist_matrix(X):
    dist = pdist(X)
    dist_matrix = squareform(dist)
    return dist_matrix

noise = 0.2
n = 60

x1 = np.random.randn(n) * noise + 0.5
y1 = np.random.randn(n) * noise + 0.5
x2 = np.random.randn(n) * noise + 0.5
y2 = np.random.randn(n) * noise - 0.5
x3 = np.random.randn(n) * noise - 0.5
y3 = np.random.randn(n) * noise + 0.5
x4 = np.random.randn(n) * noise - 0.5
y4 = np.random.randn(n) * noise - 0.5

X = np.vstack([
    np.column_stack((x1, y1)),
    np.column_stack((x2, y2)),
    np.column_stack((x3, y3)),
    np.column_stack((x4, y4)),
])

y = np.hstack([
    np.ones(n),       # Class 1
    np.zeros(n),      # Class 0
    np.zeros(n),      # Class 0
    np.ones(n),       # Class 1
])

plt.figure(figsize=(8, 6))
plt.scatter(
    X[:, 0], 
    X[:, 1], 
    c=y, 
    cmap='bwr', 
    edgecolor='k', 
    s=50
)

plt.axhline(0, color='gray', linestyle='--', linewidth=0.8)
plt.axvline(0, color='gray', linestyle='--', linewidth=0.8)
plt.grid(False)
plt.show()
plt.close()


distance_matrix = dist_matrix(X)

plt.figure(figsize=(10, 8))
plt.imshow(distance_matrix, cmap='viridis', interpolation='nearest')
plt.colorbar(label='Distance')
plt.grid(False)
plt.gca().invert_yaxis()
plt.show()
plt.close()

h = 1
n_samples = X.shape[0]
matK = np.exp(-cdist(X, X)**2 / h**2)

distance_matrix2 = dist_matrix(matK)

plt.figure(figsize=(10, 8))
plt.imshow(distance_matrix2, cmap='viridis', interpolation='nearest')
plt.colorbar(label='Distance')
plt.grid(False)

plt.gca().invert_yaxis()

plt.show()
plt.close()

class_1_idx = np.where(y == 1)[0]
class_0_idx = np.where(y == 0)[0]

print(class_1_idx)
print(class_0_idx)

k11 = matK[np.ix_(class_1_idx, class_1_idx)]
k12 = matK[np.ix_(class_1_idx, class_0_idx)]
k21 = matK[np.ix_(class_0_idx, class_1_idx)]
k22 = matK[np.ix_(class_0_idx, class_0_idx)]

sk11 = k11.sum(axis=0) / (120 * ((np.sqrt(2 * np.pi) * h**2)))
sk12 = k12.sum(axis=0) / (120 * ((np.sqrt(2 * np.pi) * h**2)))
sk21 = k21.sum(axis=0) / (120 * ((np.sqrt(2 * np.pi) * h**2)))
sk22 = k22.sum(axis=0) / (120 * ((np.sqrt(2 * np.pi) * h**2)))

plt.figure(figsize=(10, 8))
plt.scatter(sk11, sk12, color="red")
plt.scatter(sk21, sk22, color="blue")
plt.show()
