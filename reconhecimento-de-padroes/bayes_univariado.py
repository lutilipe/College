import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from scipy.stats import norm

np.random.seed(0)
class1 = np.random.normal(2, 0.8, 240)
class2 = np.random.normal(4, 0.4, 120)

labels_class1 = np.zeros(240)
labels_class2 = np.ones(120)

data = np.concatenate([class1, class2])
labels = np.concatenate([labels_class1, labels_class2])

X_train, X_test, y_train, y_test = train_test_split(data, labels, test_size=0.1, random_state=0)

mean1, std1 = 2, 0.8
mean2, std2 = 4, 0.4

def bayes_classifier(x):
    p1 = norm.pdf(x, mean1, std1)
    p2 = norm.pdf(x, mean2, std2)
    return 0 if p1 > p2 else 1

y_pred = [bayes_classifier(x) for x in X_test]

accuracy = accuracy_score(y_test, y_pred) * 100
print(f"Percentual de acertos no conjunto de teste: {accuracy:.2f}%")

plt.figure(figsize=(10, 6))

plt.scatter(X_train[y_train == 0], [0] * sum(y_train == 0), marker='x', color='blue', label="Classe 1 (Treinamento)")
plt.scatter(X_train[y_train == 1], [0] * sum(y_train == 1), marker='x', color='red', label="Classe 2 (Treinamento)")

plt.scatter(X_test[y_test == 0], [0.5] * sum(y_test == 0), marker='o', color='cyan', label="Classe 1 (Teste)")
plt.scatter(X_test[y_test == 1], [0.5] * sum(y_test == 1), marker='o', color='orange', label="Classe 2 (Teste)")

x_values = np.linspace(-1, 7, 500)
plt.plot(x_values, norm.pdf(x_values, mean1, std1), color='blue', label="Gaussiana Classe 1")
plt.plot(x_values, norm.pdf(x_values, mean2, std2), color='red', label="Gaussiana Classe 2")

plt.xlabel("Valor da variável")
plt.ylabel("Densidade de probabilidade")
plt.legend()
plt.title("Classificação Bayesiana com Distribuições Normais")

plt.savefig("grafico_classificacao.png")
plt.close()
