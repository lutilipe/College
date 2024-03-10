import numpy as np
from matplotlib import pyplot as plt
from scipy import optimize as opt

precisao = 1e-3
rg = 1
rh = 1
Cg = 5
Ch = 10
xlast = np.inf*np.ones(3)
iteracoes = 1

while True:

	def fh(vars):
		a, b, c = vars[0], vars[1], vars[2]
		gp1 = max(0, 2*(a+b)-1.5)**2
		gp2 = max(0, b - 3*a)**2
		gp3 = max(0, (3/2)*c - b)**2
		gp4 = max(0, -a)**2 + max(0, a - 0.5)**2
		gp5 = max(0, -b)**2 + max(0, b - 0.5)**2
		gp6 = max(0, -c)**2
		h1 = (a*b*c - 0.032)**2
		return 1.5*(2*a*b + 2*a*c + 2*b*c) + rg*(gp1 + gp2 + gp3 + gp4 + gp5 + gp6) + rh*h1
	
	# Ponto inicial
	x0 = np.array([1, 1, 1], dtype=float)

	sol = opt.minimize(fh, x0, method='BFGS')
	xopt = sol.x
	fopt = sol.fun

	# Exit condition
	if np.linalg.norm((xopt-xlast)/xopt) < precisao:
		break

	# Aumente u para próxima iteração
	else:
		xlast = xopt
		rg = Cg*rg
		rh = Ch*rh
		iteracoes += 1

print('--RESULTADO:--')
print('x* = ' + str(xopt))
print('f(x*) = %.3f' %fopt)
print('Valor final de rg: %.1f' % rg)
print('Valor final de rh: %.1f' % rh)
print('Número de iterações: %d' % iteracoes)