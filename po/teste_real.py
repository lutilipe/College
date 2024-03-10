import gurobipy as gp
from gurobipy import GRB

from utils import ler_dados_avioes, ler_dados_viagens, ler_matriz_de_custos

C = ler_matriz_de_custos("PCustos.xlsx")  # matriz de custos Cij

dados_viagens = ler_dados_viagens("PDados_Viagens.xlsx")

Q = dados_viagens["num_passageiros"]  # numero de passageiros por viagem
P = dados_viagens["preco_passagem"] # custo de cada passagem de uma viagem
H = dados_viagens["horario"] # horário de inicio de uma viagem
T = dados_viagens["duracao"] # duração de uma viagem

A = ler_dados_avioes("PDados_Avioes.xlsx")  # capacidade de passageiros por aviao

N = len(A)  # quantidade total de aviões disponíveis no dia
M = len(Q)  # quantidade de viagens no dia
print(N,M)
# Criação do modelo
modelo = gp.Model("designacao_de_avioes")

# Variáveis de decisão
X = modelo.addVars(N, M, vtype=GRB.BINARY, name="X")

# Função objetivo
modelo.setObjective(gp.quicksum(gp.quicksum(X[i, j] * (P[j] * Q[j] - C[j][i]) for j in range(M)) for i in range(N)), GRB.MAXIMIZE)

modelo.addConstrs((gp.quicksum(X[i, j] for i in range(N)) <= 1 for j in range(M)), "Alocacao_Total")
modelo.addConstrs((X[i, j] * Q[j] <= A[i] for i in range(N) for j in range(M)), "Capacidade_Maxima")

for k in range(M):
    L = []
    for j in range(k):
        if(H[j] + T[j] >= H[k]):
            L.append(j)
    modelo.addConstrs(gp.quicksum(X[i,j] for j in L) + X[i,k] <= 1 for i in range(N))

# Otimização
modelo.optimize()

# Impressão da solução
if modelo.status == GRB.OPTIMAL:
    print("\nSolução ótima encontrada:")
    for j in range(M):
        for i in range(N):
            if X[i, j].x > 0.5:
                print(f"Avião {i+1} designado para a viagem {j+1}")
    print(f"Lucro total: {modelo.objVal}")
else:
    print("\nO problema não possui solução ótima.")
