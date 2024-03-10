import gurobipy as gp
from gurobipy import GRB

# Dados do problema
N = 3  # quantidade total de aviões disponíveis no dia
M = 4  # quantidade de viagens no dia
C = [[10, 15, 10, 25],  # matriz de custos Cij
     [30, 25, 15, 10],
     [20, 30, 25, 15]]
Q = [50, 40, 60, 85]  # numero de passageiros por viagem
A = [90, 100, 86]  # capacidade de passageiros por aviao
P = [520, 240, 300, 200] # custo de cada passagem de uma viagem
H = [0, 10, 10, 10] # horário de inicio de uma viagem
T = [5, 15, 30, 8] # duração de uma viagem


# Criação do modelo
modelo = gp.Model("designacao_de_avioes")

# Variáveis de decisão
X = modelo.addVars(N, M, vtype=GRB.BINARY, name="X")

# Função objetivo
modelo.setObjective(gp.quicksum(gp.quicksum(X[i, j] * (P[j] * Q[j] - C[i][j]) for j in range(M)) for i in range(N)), GRB.MAXIMIZE)
            
modelo.addConstrs((gp.quicksum(X[i, j] for i in range(N)) == 1 for j in range(M)), "Alocacao_Total")
modelo.addConstrs((X[i, j] * Q[j] <= A[i] for i in range(N) for j in range(M)), "Capacidade_Maxima")

for k in range(M):
    L = []
    for j in range(k):
        if(H[j] + T[j] >= H[k]):
            L.append(j)
            
    print(L, k)
    if (len(L) == 0): continue
    modelo.addConstrs(gp.quicksum(X[i,j] for j in L) + X[i,k] <= 1 for i in range(N))

modelo.write("model.rlp")

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
