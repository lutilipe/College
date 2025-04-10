from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
import numpy as np

import numpy as np

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

data = load_breast_cancer()
X = data.data
y = data.target
print(X)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=41)

Nc1 = len(y_train[y_train == 0])
Nc2 = len(y_train[y_train == 1])

ic1 = np.where(y_train == 0)
ic2 = np.where(y_train == 1)

N = Nc1 + Nc2
Pc1 = Nc1 / N
Pc2 = Nc2 / N

Xc1 = X_train[ic1]
Xc2 = X_train[ic2]

# Teste
Nc1tst = len(y_test[y_test == 0])
Nc2tst = len(y_test[y_test == 1])

Ntst = Nc1tst + Nc2tst

ic1tst = np.where(y_test == 0)
ic2tst = np.where(y_test == 1)

Xc1tst = X_test[ic1tst]
Xc2tst = X_test[ic2tst]


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
print(f"Acuracia: {accuracy * 100:.2f}%")
MC = confusion_matrix(y_test, Yhattst)

print(MC)

TN = MC[0, 0]
FP = MC[0, 1]
FN = MC[1, 0]
TP = MC[1, 1]

specificity = TN/(TN+FP)
sensitivity = TP/(TP+FN)

print(f"Especificidade: {specificity}")
print(f"Sensibilidade: {sensitivity}")
