from sklearn.datasets import load_breast_cancer
from sklearn.metrics import confusion_matrix, accuracy_score, silhouette_samples, silhouette_score
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.metrics.pairwise import pairwise_distances

from scipy.spatial import distance_matrix

data = load_breast_cancer()
X = data.data
y = data.target

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


sorted_indices = np.argsort(y)
X_sorted = X_scaled[sorted_indices]
y_sorted = y[sorted_indices]

dist_matrix_sorted = pairwise_distances(X_sorted)
kmeans=KMeans(n_clusters=2, random_state=42)
kmeans.fit(X_sorted)

labels = kmeans.labels_

silhouette_avg = silhouette_score(X_sorted, labels)
print(
    "silhouette_score media:",
    silhouette_avg,
)

sample_silhouette_values = silhouette_samples(X_sorted, labels)
print(sample_silhouette_values)
acc = accuracy_score(y_sorted, labels)
print(f"Acuracia: {acc * 100}%")

