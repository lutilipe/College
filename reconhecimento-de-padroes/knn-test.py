import os
import numpy as np
import matplotlib.pyplot as plt
import glob
from sklearn.model_selection import train_test_split

N1 = 100
N2 = 100
n = 2
k_values = range(1, 21)
num_trials = 10
sd = 0.3


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

def run_experiment(k):
    accuracies = []

    for _ in range(num_trials):
        xc1 = np.random.normal(0, sd, (N1, n)) + np.array([[3, 4]])
        xc2 = np.random.normal(0, sd, (N2, n)) + np.array([[4, 3]])

        X = np.vstack((xc1, xc2))
        y = np.array([-1] * N1 + [1] * N2)

        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=None)

        points = {-1: X_train[y_train == -1], 1: X_train[y_train == 1]}
        
        correct = 0
        for i, point in enumerate(X_test):
            prediction = knn(points, point, k)
            if prediction == y_test[i]:
                correct += 1

        accuracy = correct / len(y_test)
        accuracies.append(accuracy)
    
    return np.mean(accuracies), np.std(accuracies)

mean_accuracies = []
std_accuracies = []

for k in k_values:
    mean_accuracy, std_accuracy = run_experiment(k)
    mean_accuracies.append(mean_accuracy)
    std_accuracies.append(std_accuracy)

plt.figure(figsize=(10, 6))
plt.errorbar(k_values, mean_accuracies, yerr=std_accuracies, fmt='-o', ecolor='red', capsize=5)
plt.xlabel('Valor de k')
plt.ylabel('Acurácia Média')
plt.title('Desempenho do KNN em função de k')
plt.grid(True)
plt.show()