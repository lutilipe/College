import os
import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVC
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.model_selection import GridSearchCV

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

def run_with_cv():
    X, y = generate_spiral_points(n_points=1000, noise=1)
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, random_state=42)
    
    param_grid = {
        'C': [0.1, 1, 10, 50, 100, 200, 500, 700, 1000],
    }
    
    svc = SVC()
    grid_search = GridSearchCV(svc, param_grid, cv=10, scoring='accuracy')
    grid_search.fit(X_train, y_train)
    
    best_svc = grid_search.best_estimator_
    print(f"Melhores parâmetros: {grid_search.best_params_}")
    
    y_pred = best_svc.predict(X_test)
    accuracy = accuracy_score(y_test, y_pred)
    print(f"Acurácia: {accuracy:.2f}")

    xx, yy = np.meshgrid(np.linspace(X[:, 0].min() - 1, X[:, 0].max() + 1, 100),
                         np.linspace(X[:, 1].min() - 1, X[:, 1].max() + 1, 100))

    Z = best_svc.decision_function(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)

    plt.contourf(xx, yy, Z, levels=np.linspace(Z.min(), 0, 7), cmap="coolwarm", alpha=0.3)
    plt.contour(xx, yy, Z, levels=[0], linewidths=2, colors="k")
    plt.scatter(X_train[:, 0], X_train[:, 1], c=y_train, s=30, cmap="coolwarm")
    
    plt.scatter(best_svc.support_vectors_[:, 0], best_svc.support_vectors_[:, 1], 
                s=100, facecolors="none", edgecolors="k", label="Vetores de Suporte")

    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("SVM com Cross-Validation")
    plt.legend()
    plt.show()

def run(c):
    X, y = generate_spiral_points(n_points=1000, noise=1)
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, random_state=42)
    plt.scatter(X[:, 0], X[:, 1], c=y, s=30, cmap="coolwarm")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("SVM")
    plt.show()
    plt.close()

    svc = SVC(C=c, gamma="scale", kernel="rbf")
    svc.fit(X_train, y_train)

    y_pred = svc.predict(X_test)
    accuracy = accuracy_score(y_test, y_pred)
    print(f"Acuracia: {accuracy:.2f}")

    xx, yy = np.meshgrid(np.linspace(X[:, 0].min() - 1, X[:, 0].max() + 1, 100),
                         np.linspace(X[:, 1].min() - 1, X[:, 1].max() + 1, 100))

    Z = svc.decision_function(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)

    plt.scatter(X_train[:, 0], X_train[:, 1], c=y_train, s=30, cmap="coolwarm")
    plt.scatter(svc.support_vectors_[:, 0], svc.support_vectors_[:, 1], s=100, facecolors="none", edgecolors="green", label="Vetores de Suporte")

    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("SVM")
    plt.legend()
    plt.show()
    plt.close()

    plt.contourf(xx, yy, Z, levels=np.linspace(Z.min(), 0, 7), cmap="coolwarm", alpha=0.3)
    plt.contour(xx, yy, Z, levels=[0], linewidths=2, colors="k")
    plt.scatter(X_train[:, 0], X_train[:, 1], c=y_train, s=30, cmap="coolwarm")

    plt.scatter(svc.support_vectors_[:, 0], svc.support_vectors_[:, 1], s=100, facecolors="none", edgecolors="green", label="Vetores de Suporte")

    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("SVM")
    plt.legend()
    plt.show()

run(c=100)
#run_with_cv()