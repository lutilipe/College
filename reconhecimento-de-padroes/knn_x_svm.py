from sklearn.datasets import load_breast_cancer
import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVC
from sklearn.model_selection import cross_val_score, KFold
import math

breast_cancer = load_breast_cancer()
X, y = breast_cancer.data, breast_cancer.target


breast_cancer = load_breast_cancer()
X, y = breast_cancer.data, breast_cancer.target

def calc(points, p, h=2, k=3):
    dist = []
    for group in points:
        for feature in points[group]:
            euclidean_distance = np.linalg.norm(feature - p)
            dist.append((math.exp(-(euclidean_distance / (h * h))), group))
    
    sorted_dist = sorted(dist, key=lambda x: x[0], reverse=True)[:k]

    q0 = sum(d[0] for d in sorted_dist if d[1] == 0)
    q1 = sum(d[0] for d in sorted_dist if d[1] == 1)

    return 1 if q1 > q0 else 0

def knn():
    h_values = [0.5, 0.7, 0.9] + list(range(1, 101, 4))
    k_values = range(1, 201, 10)
    
    kf = KFold(n_splits=10)
    accuracies = {k: [] for k in k_values}
    
    for k in k_values:
        for h in h_values:
            fold_accuracies = []
            
            for train_index, test_index in kf.split(X):
                X_train, X_test = X[train_index], X[test_index]
                y_train, y_test = y[train_index], y[test_index]

                fold_points = {0: [], 1: []}
                for i, label in enumerate(y_train):
                    fold_points[label].append(X_train[i])
                
                predictions = []
                for point in X_test:
                    prediction = calc(fold_points, point, h, k=k)
                    predictions.append(prediction)

                accuracy = np.mean(predictions == y_test)
                fold_accuracies.append(accuracy)

            avg_accuracy = np.mean(fold_accuracies)
            accuracies[k].append(avg_accuracy)

    best_k, best_h, best_accuracy = None, None, 0
    for k in k_values:
        for i, h in enumerate(h_values):
            if accuracies[k][i] > best_accuracy:
                best_k, best_h, best_accuracy = k, h, accuracies[k][i]

    print(f'Best parameters: k={best_k}, h={best_h} with accuracy={best_accuracy:.4f}')


    # Plot the results
    _, axes = plt.subplots(abs(len(k_values) / 2), len(k_values), figsize=(15, 6), sharey=True)

    for i, k in enumerate(k_values):
        axes[i].plot(h_values, accuracies[k], marker='o', label=f'k={k}')
        axes[i].set_title(f'KNN Accuracy for k={k}')
        axes[i].set_xlabel('Bandwidth (h)')
        axes[i].set_ylabel('Accuracy')
        axes[i].grid()

    plt.tight_layout()
    plt.show()

def svm():
    kernels = ['poly', 'rbf', 'sigmoid', 'linear']
    accuracies = []

    for kernel in kernels:
        svc = SVC(kernel=kernel, C=10) 
        scores = cross_val_score(svc, X, y, cv=10)
        accuracies.append(scores.mean())

    colors = plt.cm.coolwarm(np.linspace(0, 1, len(kernels)))

    plt.figure(figsize=(8, 6))
    bars = plt.bar(kernels, accuracies, color=colors)
    
    for bar in bars:
        height = bar.get_height()
        plt.text(bar.get_x() + bar.get_width()/2., height, f'{height:.2f}', ha='center', va='bottom', color='black')

    plt.title('SVM - Acurácia Média por Kernel')
    plt.xlabel('Kernel')
    plt.ylabel('Acurácia Média')

    plt.show()

#svm()
knn()