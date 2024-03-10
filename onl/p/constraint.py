import inspect
import numpy as np
from scipy import optimize as opt
import time as tm


class Result:
    def __init__(self, x=None, fx=None, path=None, niter=None, nevals=None,
                 time=None, slack=None):
        self.x = x
        self.fx = fx
        self.path = path
        self.niter = niter
        self.nevals = nevals
        self.time = time
        self.slack = slack


def expenalty(f, x0, g=None, h=None, u0=1., alpha=1.5, precision=1e-3,
              maxiter=1000, method='BFGS'):
    
    if g is None:
        ninequality = 0
    elif inspect.isfunction(g):
        ninequality = 1
        g = [g]
    else:
        ninequality = len(g)
    
    if h is None:
        nequality = 0
    elif inspect.isfunction(h):
        nequality = 1
        h = [h]
    else:
        nequality = len(h)

    if type(u0) is float or type(u0) is int:
        u = u0*np.ones(ninequality + nequality)
    elif type(u0) is list:
        u = np.array(u0)
    elif type(u0) is np.ndarray:
        u = u0.copy()

    if type(x0) is list:
        x = np.array(x0, dtype=float)
    else:
        x = x0.copy()

    N = x.size
    xlast = np.inf*np.ones(N)
    path = [x.copy()]
    k = 1
    nevals = 0
    execution_time = 0.

    while True:
    
        tic = tm.time()
    
        def fh(vars):
            
            y = f(vars)
            i = 0
            
            for j in range(ninequality):
                y += u[i]*max(0, g[j](vars))**2
                i += 1

            for j in range(nequality):
                y += u[i]*h[j](vars)**2
                i += 1

            return y
    
        solution = opt.minimize(fh, x, method=method)
        x = solution.x
        nevals += solution.nfev
    
        if k == maxiter:
            break
        elif np.linalg.norm(x-xlast)/np.linalg.norm(x) < precision:
            break
        else:
            xlast = x.copy()
            k += 1
            u = u*alpha
            path.append(x.copy())
            execution_time += tm.time()-tic

    slack = np.zeros(ninequality + nequality)
    i = 0
    for j in range(ninequality):
        slack[i] = g[j](x)
        i += 1
    for j in range(nequality):
        slack[i] = h[j](x)
        i += 1

    execution_time += tm.time()-tic
    result = Result(x=x, fx=f(x), path=np.array(path), niter=k, nevals=nevals,
                    time=execution_time, slack=slack)
    result.u = u
    
    return result


def inpenalty(f, x0, g=None, u0=1., alpha=1.5, precision=1e-3, maxiter=1000,
              method='BFGS'):
    
    if g is None:
        ninequality = 0
    elif inspect.isfunction(g):
        ninequality = 1
        g = [g]
    else:
        ninequality = len(g)

    if type(u0) is float or type(u0) is int:
        u = u0*np.ones(ninequality)
    elif type(u0) is list:
        u = np.array(u0)
    elif type(u0) is np.ndarray:
        u = u0.copy()

    if type(x0) is list:
        x = np.array(x0, dtype=float)
    else:
        x = x0.copy()

    N = x.size
    xlast = np.inf*np.ones(N)
    path = [x.copy()]
    k = 1
    nevals = 0
    execution_time = 0.
    slack = np.zeros(ninequality)

    while True:
    
        tic = tm.time()
    
        def fh(vars):
            
            y = f(vars)
            
            for j in range(ninequality):
                y -= u[j]/g[j](vars)

            return y
    
        solution = opt.minimize(fh, x, method=method)
        x = solution.x
        nevals += solution.nfev
        
        for j in range(ninequality):
            slack[j] = g[j](x)
    
        if k == maxiter:
            break
        elif np.linalg.norm(x-xlast)/np.linalg.norm(x) < precision:
            break
        elif np.any(slack > 0.):
            # u = u*alpha
            # alpha = alpha*2
            x = xlast.copy()
            # k += 1
            execution_time += tm.time()-tic
            break
        
        else:
            xlast = x.copy()
            k += 1
            u = u/alpha
            path.append(x.copy())
            execution_time += tm.time()-tic

    execution_time += tm.time()-tic
    result = Result(x=x, fx=f(x), path=np.array(path), niter=k, nevals=nevals,
                    time=execution_time, slack=slack)
    result.u = u
    
    return result


def alm(f, x0, g=None, h=None, mu0=0., lambda0=0., u0=1., alpha=1.5,
        precision=1e-3, maxiter=1000, method='BFGS'):
    
    if g is None:
        ninequality = 0
    elif inspect.isfunction(g):
        ninequality = 1
        g = [g]
    else:
        ninequality = len(g)
    
    if h is None:
        nequality = 0
    elif inspect.isfunction(h):
        nequality = 1
        h = [h]
    else:
        nequality = len(h)

    if type(u0) is float or type(u0) is int:
        u = u0*np.ones(ninequality + nequality)
    elif type(u0) is list:
        u = np.array(u0)
    elif type(u0) is np.ndarray:
        u = u0.copy()

    if type(mu0) is float or type(mu0) is int:
        mu = mu0*np.ones(ninequality)
    elif type(mu0) is list:
        mu = np.array(mu0)
    elif type(mu0) is np.ndarray:
        mu = mu0.copy()
    
    if type(lambda0) is float or type(lambda0) is int:
        lam = lambda0*np.ones(nequality)
    elif type(lambda0) is list:
        lam = np.array(lambda0)
    elif type(lambda0) is np.ndarray:
        lam = lambda0.copy()

    if type(x0) is list:
        x = np.array(x0, dtype=float)
    else:
        x = x0.copy()

    N = x.size
    xlast = np.inf*np.ones(N)
    path = [x.copy()]
    k = 1
    nevals = 0
    execution_time = 0.

    while True:
    
        tic = tm.time()
    
        def L(vars):
            
            y = f(vars)
            i = 0
            
            for j in range(ninequality):
                y += u[i]/2*max(g[j](vars), mu[j]/u[i])**2
                i += 1

            for j in range(nequality):
                y += u[i]*(h[j](vars) + lam[j]/u[i])**2
                i += 1

            return y
    
        solution = opt.minimize(L, x, method=method)
        x = solution.x
        nevals += solution.nfev
    
        if k == maxiter:
            break
        elif np.linalg.norm(x-xlast)/np.linalg.norm(x) < precision:
            break
        else:
            i = 0
            for j in range(ninequality):
                mu[j] += u[i]*max(g[j](x), -mu[j]/u[i])
                i += 1
            for j in range(nequality):
                lam[j] += u[i]*h[j](x)
                i += 1
            
            xlast = x.copy()
            k += 1
            u = u*alpha
            path.append(x.copy())
            execution_time += tm.time()-tic

    slack = np.zeros(ninequality + nequality)
    i = 0
    for j in range(ninequality):
        slack[i] = g[j](x)
        i += 1
    for j in range(nequality):
        slack[i] = h[j](x)
        i += 1

    execution_time += tm.time()-tic
    result = Result(x=x, fx=f(x), path=np.array(path), niter=k, nevals=nevals,
                    time=execution_time, slack=slack)
    result.u = u
    result.lam = lam
    result.mu = mu
    
    return result