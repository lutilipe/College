import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.spatial.distance import cdist, pdist, squareform
from sklearn.model_selection import KFold
from sklearn.metrics import accuracy_score
from sklearn.model_selection import ParameterGrid

def dist_matrix(X):
    dist = pdist(X)
    dist_matrix = squareform(dist)
    return dist_matrix

# Load data
data = pd.read_csv('sonar.all-data', header=None)
X = data.iloc[:, :-1].values  # Features
y = data.iloc[:, -1].values   # Classes

# Map classes to numerical values
y = np.where(y == 'R', 0, 1)

kf = KFold(n_splits=10, shuffle=True, random_state=42)
param_grid = {'h': np.linspace(0.1, 1.0, 10)}
best_h = None
best_accuracy = 0
all_results = []

for params in ParameterGrid(param_grid):
    h = params['h']
    accuracies = []

    fig, axes = plt.subplots(2, 5, figsize=(20, 10))
    plt.suptitle(f"Plot - h = {h}", fontsize=16, fontweight='bold')

    axes = axes.ravel()

    for fold_idx, (train_idx, test_idx) in enumerate(kf.split(X)):
        # Split data into training and testing sets
        X_train, X_test = X[train_idx], X[test_idx]
        y_train, y_test = y[train_idx], y[test_idx]

        # Compute kernel matrix using training data
        matK = np.exp(-cdist(X_train, X_train)**2 / h**2)

        # Separate kernel matrix by class
        class_1_idx = np.where(y_train == 1)[0]
        class_0_idx = np.where(y_train == 0)[0]

        k11 = matK[np.ix_(class_1_idx, class_1_idx)]
        k12 = matK[np.ix_(class_1_idx, class_0_idx)]
        k21 = matK[np.ix_(class_0_idx, class_1_idx)]
        k22 = matK[np.ix_(class_0_idx, class_0_idx)]

        # Compute likelihoods
        normalization_factor = X_train.shape[0] * ((np.sqrt(2 * np.pi) * h) ** 2)
        sk11 = k11.sum(axis=1) / normalization_factor
        sk12 = k12.sum(axis=1) / normalization_factor
        sk21 = k21.sum(axis=1) / normalization_factor
        sk22 = k22.sum(axis=1) / normalization_factor

        # Visualize likelihoods for the current fold
        ax = axes[fold_idx]
        ax.set_title(f"Fold {fold_idx + 1}")
        ax.scatter(sk11, sk12, color="red", label="Classe 1 (Metal)")
        ax.scatter(sk21, sk22, color="blue", label="Classe 0 (Rock)")
        ax.set_xlabel("Classe 1 (Metal)")
        ax.set_ylabel("Classe 0 (Rock)")
        ax.legend()

        # Test kernel matrix
        test_kernel = np.exp(-cdist(X_test, X_train)**2 / h**2)

        # Predict classes based on likelihoods
        likelihood_class_1 = test_kernel[:, class_1_idx].sum(axis=1) / normalization_factor
        likelihood_class_0 = test_kernel[:, class_0_idx].sum(axis=1) / normalization_factor

        predictions = np.where(likelihood_class_1 > likelihood_class_0, 1, 0)

        # Calculate accuracy for this fold
        accuracy = accuracy_score(y_test, predictions)
        accuracies.append(accuracy)

    plt.tight_layout()
    plt.savefig(f"h{h}.png", format="png")

    mean_accuracy = np.mean(accuracies)
    std = np.std(accuracies)
    all_results.append((h, mean_accuracy, std))
    if mean_accuracy > best_accuracy:
        best_accuracy = mean_accuracy
        best_h = h

# Print overall results
print(f"Melhor h: {best_h}, com acurácia média de: {best_accuracy:.4f}")
for h, acc, std in all_results:
    print(f"h = {h:.2f}, acurácia média = {acc:.4f}, std = {std:.4f}")