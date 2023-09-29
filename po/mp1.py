import gurobipy as gp
from gurobipy import GRB

# Criação do modelo
modelo = gp.Model("Maximizar_Lucro_Agricultor")

# Variáveis de decisão
x1 = modelo.addVar()
x2 = modelo.addVar()

# Função objetivo: Maximizar o lucro total
modelo.setObjective(4*x1 +  x2, GRB.MINIMIZE)

# Restrições
modelo.addConstr(3*x1 + x2 == 3)
modelo.addConstr(4*x1 + 3*x2 >= 6)
modelo.addConstr(x1 + 2*x2 <= 4)

# Otimização
modelo.optimize()

# Resultados
if modelo.status == GRB.OPTIMAL:
    print("Optimal Solution:")
    for var in modelo.getVars():
        print(f"{var.varName}: {var.x}")
    
    print(f"Optimal Objective Value: {modelo.objVal}")

    # Get dual values
    print("Dual Values:")
    for constr in modelo.getConstrs():
        print(f"{constr.ConstrName}: {constr.Pi}")

else:
    print("The problem is infeasible or unbounded.")

# Fechando o modelo
modelo.close()