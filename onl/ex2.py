import numpy as np
from matplotlib import pyplot as plt
from scipy import optimize

x = np.array([3, 3], dtype=float) # Ponto inicial
mu1 = 0. # Multiplicador de Lagrange (desigualdade) p/ g1
mu2 = 0. # Multiplicador de Lagrange (desigualdade) p/ g2
mu3 = 0. # Multiplicador de Lagrange (desigualdade) p/ g3
mu4 = 0. # Multiplicador de Lagrange (desigualdade) p/ g4
mu5 = 0. # Multiplicador de Lagrange (desigualdade) p/ g5
mu6 = 0. # Multiplicador de Lagrange (desigualdade) p/ g6
mu7 = 0. # Multiplicador de Lagrange (desigualdade) p/ g7
u = 1. # Constante de penalidade
alpha = 5 # Aceleração da penalização
k = 1 # Contador de iterações
precision = 1e-2
history = [x] # Histórico das variáveis de decisão
xlast = x.copy() # 

# Processo iterativo
while True:
    
    # Definição da função Lagrangeana que será a
    # função-objetivo do problema transformado
    def L(vars):
        x1, x2 = vars[0], vars[1]
        g1 = 20*((x2 + x1*np.sqrt(2)) / (x1**2 * np.sqrt(2) + 2*x1*x2)) - 20
        g2 = 20*(1 / (x1 + x2*np.sqrt(2))) - 20
        g3 = -20*(x2 / (x1**2 * np.sqrt(2) + 2*x1*x2)) + 15
        g4 = -x1 + 0.1
        g5 = x1 - 5
        g6 = -x2 + 0.1
        g7 = x2 - 5
        f = 2*np.sqrt(2)*x1 + x2
        return f + u/2*max(0, g1)**2 + mu2*g2 + u/2*max(0, g2)**2  + mu3*g3 + u/2*max(0, g3)**2 + mu4*g4 + u/2*max(0, g4)**2 + mu5*g5 + u/2*max(0, g5)**2 + mu6*g6 + u/2*max(0, g6)**2 + mu7*g7 + u/2*max(0, g7)**2
    
    # Resolve problema de otimização irrestrito
    solution = optimize.minimize(L, x, method='BFGS')
    
    # Atualização da variável de decisão
    x = solution.x
    
    print('Iteração %d' % k, end=' - ')
    print('x-ótimo: ' + str(x), end=', ')
    print('mu 1 = %.2f' % mu1, end=', ')
    print('mu 2 = %.2f' % mu2, end=', ')
    print('mu 3 = %.2f' % mu3, end=', ')
    print('mu 4 = %.2f' % mu4, end=', ')
    print('mu 5 = %.2f' % mu5, end=', ')
    print('mu 6 = %.2f' % mu6, end=', ')
    print('mu 7 = %.2f' % mu7, end=', ')
    print('u = %.2f' % u)
    
    # Atualização do multiplicador de Lagrange
    mu1 = mu1 + u*max(20*((x[1] + x[0]*np.sqrt(2)) / (x[0]**2 * np.sqrt(2) + 2*x[0]*x[1])) - 20, -mu1/u)
    mu2 = mu2 + u*max(20*(1 / (x[0] + x[1]*np.sqrt(2))) - 20, -mu2/u)
    mu3 = mu3 + u*max(-20*(x[1] / (x[0]**2 * np.sqrt(2) + 2*x[0]*x[1])) + 15, -mu3/u)
    mu4 = mu4 + u*max(-x[0] + 0.1, -mu4/u)
    mu5 = mu5 + u*max(x[0] - 5, -mu5/u)
    mu6 = mu6 + u*max(x[1] - 5, -mu6/u)
    mu7 = mu7 + u*max(-x[1] + 0.1, -mu7/u)
    
    # Atualização da constante de penalização
    u = alpha*u
    
    # Atualização das iterações
    k += 1
    
    # Salva informação do novo ponto encontrado
    history.append(x)
    
    if np.linalg.norm(x-xlast)/np.linalg.norm(x) < precision:
        break
    else:
        xlast = x.copy()
