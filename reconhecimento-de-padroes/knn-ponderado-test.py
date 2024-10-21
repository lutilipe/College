import os
import numpy as np
import matplotlib.pyplot as plt
import math
from sklearn.model_selection import train_test_split

N1 = 100
N2 = 100
n = 2
k_values = range(1, 51)
num_trials = 10
sd = 0.3

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

def run_experiment(k):
    accuracies = []

    xc1 = np.random.normal(0, sd, (N1, n)) + np.array([[3, 4]])
    xc2 = np.random.normal(0, sd, (N2, n)) + np.array([[4, 3]])

    X = np.vstack((xc1, xc2))
    y = np.array([-1] * N1 + [1] * N2)

    for _ in range(num_trials):

        
        #X, y = generate_spiral_points(n_points=200, noise=0.6)

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