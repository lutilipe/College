from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler

# Função para calcular o valor da PDF de uma variável normal multivariada
def pdfnvar(x, m, K, n):
    x = np.array(x)
    m = np.array(m)
    K = np.array(K)
    
    det_K = np.linalg.det(K)
    inv_K = np.linalg.inv(K)
    
    diff = x - m
    exponent = -0.5 * np.dot(diff.T, np.dot(inv_K, diff))
    
    factor = 1 / (np.sqrt((2 * np.pi) ** n * det_K))
    pdf_value = factor * np.exp(exponent)
    
    return pdf_value

def bayes(X, y):
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, random_state=42)

    Nc1 = len(y_train[y_train == 0])
    Nc2 = len(y_train[y_train == 1])

    ic1 = np.where(y_train == 0)
    ic2 = np.where(y_train == 1)

    N = Nc1 + Nc2
    Pc1 = Nc1 / N
    Pc2 = Nc2 / N

    Xc1 = X_train[ic1]
    Xc2 = X_train[ic2]

    X_train_0 = X_train[y_train == 0]
    X_train_1 = X_train[y_train == 1]
    X_test_0 = X_test[y_test == 0]
    X_test_1 = X_test[y_test == 1]

    m1 = np.mean(Xc1, axis=0)
    m2 = np.mean(Xc2, axis=0)

    k1 = np.cov(Xc1, rowvar=False)
    k2 = np.cov(Xc2, rowvar=False)

    Yhattst = np.zeros(len(y_test))
    for i in range(len(y_test)):
        Pc1_x = pdfnvar(X_test[i,], m1, k1, X.shape[1]) * Pc1 
        Pc2_x = pdfnvar(X_test[i,], m2, k2, X.shape[1]) * Pc2

        Yhattst[i] = 1 if Pc2_x > Pc1_x else 0

    accuracy = np.sum(Yhattst == y_test) / len(y_test)
    print(f"Acurácia: {accuracy * 100:.2f}%")

    plt.figure(figsize=(8, 6))
    
    plt.scatter(X_train_0[:, 0], X_train_0[:, 1], marker='o', label='Treinamento Classe 0', edgecolors='k',color="blue",  alpha=0.5)
    plt.scatter(X_test_0[:, 0], X_test_0[:, 1], marker='x', label='Teste Classe 0', color="blue",edgecolors='k')
    plt.scatter(X_train_1[:, 0], X_train_1[:, 1], marker='o', label='Treinamento Classe 1', edgecolors='k', color="red",alpha=0.5)
    plt.scatter(X_test_1[:, 0], X_test_1[:, 1], marker='x', label='Teste Classe 1', color="red",edgecolors='k')
    
    h = .02 
    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))

    Z = np.zeros(xx.shape)
    for i in range(xx.shape[0]):
        for j in range(xx.shape[1]):
            Pc1_x = pdfnvar([xx[i, j], yy[i, j]], m1, k1, X.shape[1]) * Pc1
            Pc2_x = pdfnvar([xx[i, j], yy[i, j]], m2, k2, X.shape[1]) * Pc2
            Z[i, j] = 1 if Pc2_x > Pc1_x else 0

    plt.contourf(xx, yy, Z, alpha=0.3, cmap='coolwarm')
    
    plt.xlabel('x1')
    plt.ylabel('x2')
    plt.title(f'Superfície de Decisão')
    plt.legend()
    plt.show()

# 1
mean1 = [2, 2]
mean2 = [4, 4]
cov1 = [[0.8**2, 0], [0, 0.8**2]]
cov2 = [[0.4**2, 0], [0, 0.4**2]]
n_samples = 200

data_class1 = np.random.multivariate_normal(mean1, cov1, n_samples)
data_class2 = np.random.multivariate_normal(mean2, cov2, n_samples)

N1 = len(data_class1)
N2 = len(data_class2)
n_samples = N1 + N2

X = np.vstack((data_class1, data_class2))
y = np.array([0] * N1 + [1] * N2)
bayes(X,y)


# 2
mean1 = [1, 1]
mean2 = [1, 4]
mean3 = [4, 1]
mean4 = [4, 4]

cov1 = np.array([[0.3, 0.1], [0.1, 0.3]])
cov2 = np.array([[0.3, -0.1], [-0.1, 0.3]])
cov3 = np.array([[0.3, 0.2], [0.2, 0.3]])
cov4 = np.array([[0.3, -0.2], [-0.2, 0.3]])

class1 = np.random.multivariate_normal(mean1, cov1, 100)
class2 = np.random.multivariate_normal(mean4, cov4, 100)
class3 = np.random.multivariate_normal(mean2, cov2, 100)
class4 = np.random.multivariate_normal(mean3, cov3, 100)

X = np.vstack([class1, class2, class3, class4])
y = np.array([0] * 200 + [1] * 200)

bayes(X,y)