from sklearn.model_selection import KFold
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


data = pd.read_csv('parkinson.data')

X = data.drop(columns=['status', 'name'])
y = data['status']

# Padronizar os dados
scaler = StandardScaler()
X = scaler.fit_transform(X)

# Inicializar KFold
kf = KFold(n_splits=10, shuffle=True)

accuracies = []

# Loop para realizar a validação cruzada de 10 folds
for fold, (train_index, test_index) in enumerate(kf.split(X), 1):
    X_train, X_test = X[train_index], X[test_index]
    y_train, y_test = y[train_index], y[test_index]

    Nc1 = len(y_train[y_train == 0])
    Nc2 = len(y_train[y_train == 1])

    ic1 = np.where(y_train == 0)
    ic2 = np.where(y_train == 1)

    N = Nc1 + Nc2
    Pc1 = Nc1 / N
    Pc2 = Nc2 / N

    Xc1 = X_train[ic1]
    Xc2 = X_train[ic2]

    m1 = np.mean(Xc1, axis=0)
    m2 = np.mean(Xc2, axis=0)

    k1 = np.cov(Xc1, rowvar=False)
    k2 = np.cov(Xc2, rowvar=False)

    # Predição
    Yhattst = np.zeros(len(y_test))
    for i in range(len(y_test)):
        Pc1_x = pdfnvar(X_test[i,], m1, k1, X.shape[1]) * Pc1 
        Pc2_x = pdfnvar(X_test[i,], m2, k2, X.shape[1]) * Pc2

        Yhattst[i] = 1 if Pc2_x > Pc1_x else 0

    accuracy = np.sum(Yhattst == y_test) / len(y_test)
    accuracies.append(accuracy)
    
    # Exibir a matriz de confusão para cada fold (opcional)
    MC = confusion_matrix(y_test, Yhattst)
    TN, FP, FN, TP = MC.ravel()

    specificity = TN / (TN + FP)
    sensitivity = TP / (TP + FN)
    
    print(f"Fold {fold} - Acurácia: {accuracy * 100:.2f}%")
    print(f"Especificidade: {specificity:.2f}")
    print(f"Sensibilidade: {sensitivity:.2f}")

# Acurácia média e desvio padrão
mean_accuracy = np.mean(accuracies)
std_accuracy = np.std(accuracies)

print(f"\nAcurácia Média: {mean_accuracy * 100:.2f}%")
print(f"Desvio Padrão: {std_accuracy * 100:.2f}%")

# Gráfico das acurácias de cada fold
plt.figure(figsize=(8, 6))
plt.plot(range(1, 11), accuracies, marker='o', linestyle='-', color='b', label='Acurácia por Fold')
plt.xlabel('Fold')
plt.ylabel('Acurácia')
plt.title('Acurácia por Fold (Validação Cruzada 10-Folds)')
plt.xticks(range(1, 11))
plt.grid(True)
plt.show()
