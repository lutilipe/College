import gurobipy as gp
from gurobipy import GRB

# Dados do problema
N = 10  # quantidade total de aviões disponíveis no dia
M = 15  # quantidade de viagens no dia
C = [
    [10000, 15000, 10000, 25000, 12000, 30000, 8000, 10000, 20000, 25000, 18000, 15000, 12000, 22000, 18000],  
    [30000, 25000, 15000, 10000, 13000, 15000, 11000, 12000, 22000, 18000, 12000, 25000, 20000, 28000, 25000],
    [20000, 30000, 25000, 15000, 11000, 23000, 13000, 20000, 18000, 22000, 25000, 12000, 15000, 25000, 20000],
    [15000, 28000, 28000, 17000, 8000, 20000, 19000, 10000, 15000, 20000, 12000, 18000, 25000, 30000, 22000],
    [18000, 25000, 20000, 12000, 15000, 25000, 22000, 18000, 12000, 25000, 20000, 28000, 25000, 15000, 13000],
    [22000, 18000, 22000, 25000, 12000, 18000, 25000, 20000, 28000, 25000, 15000, 13000, 11000, 19000, 17000],
    [25000, 20000, 28000, 25000, 15000, 13000, 11000, 19000, 17000, 22000, 18000, 25000, 20000, 12000, 15000],
    [12000, 22000, 18000, 25000, 20000, 28000, 25000, 15000, 13000, 11000, 19000, 17000, 22000, 15000, 12000],
    [18000, 25000, 20000, 28000, 25000, 15000, 13000, 11000, 19000, 17000, 22000, 12000, 15000, 25000, 22000],
    [25000, 30000, 22000, 15000, 12000, 25000, 20000, 28000, 25000, 15000, 13000, 11000, 19000, 17000, 22000]
]
Q = [50, 40, 60, 85, 40, 70, 75, 55, 80, 120, 100, 60, 90, 110, 70]  # numero de passageiros por viagem
A = [90, 70, 80, 85, 150, 100, 120, 90, 50, 60]  # capacidade de passageiros por aviao
P = [240, 520, 300, 200, 350, 400, 320, 280, 200, 300, 400, 350, 480, 350, 180] # custo de cada passagem de uma viagem
H = [0, 10, 20, 40, 70, 110, 120, 125, 125, 130, 150, 155, 155, 160, 180] # horário de inicio de uma viagem
T = [5, 15, 30, 8, 12, 25, 28, 15, 32, 20, 21, 15, 10, 4, 15] # duração de uma viagem

H.sort()

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
