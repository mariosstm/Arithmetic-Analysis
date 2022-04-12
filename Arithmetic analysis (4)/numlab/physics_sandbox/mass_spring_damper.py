#!/usr/bin/env python2

# import algopy as alg
import numpy as np
import sympy as sp
import matplotlib.pyplot as plt
from scipy.integrate import odeint
from physics import System, Particle

m = 1.0
k = 5.0
d = .0
qy0 = -5.0
uy0 = 0.0

system = System()
msd = Particle(m)
system.addComponent(msd)
state = system.initializeState()
msd.setQ(state, np.array([0, qy0, 0]))
msd.setU(state, np.array([0, uy0, 0]))
msd.applyForce(lambda state: -d * msd.getU(state) - k * msd.getQ(state))


def dydt(y, t):
    """
    """
    system.setFromY(state, y)
    return system.getYDot(state)


# def dydtJacobian(y, t):
#     """
#     """
#     ay = alg.UTPM.init_jacobian(y)
#     return alg.UTPM.extract_jacobian(dydt(ay, t))


# cg = alg.CGraph()
# y = alg.Function(x=[1, 2, 3, 4, 5, 6])
# t = alg.Function(x=[1])
# yDot = dydt(y, t)
# cg.trace_off()
# cg.independentFunctionList = [y, t]
# cg.dependentFunctionList = [yDot]
# print cg.gradient(y0, 0)

# numerical solution
t = np.linspace(0, 20, 200)
y0 = system.getY(state)
y = odeint(dydt, y0, t)

# analytical solution
sol = sp.solve('m * x**2 + d * x + k', 'x')
sys_sol = sp.solve(['A + B - qy0', '-x1 * A - x2 * B - uy0'], 'A', 'B')
par = {'m': m, 'd': d, 'k': k}
x1 = sol[0].subs(par)
x2 = sol[1].subs(par)
par['x1'] = x1
par['x2'] = x2
par['qy0'] = qy0
par['uy0'] = uy0
A = sys_sol[sp.symbols('A')].subs(par)
B = sys_sol[sp.symbols('B')].subs(par)
tt = sp.symbols('t')
yy = sp.lambdify(tt, A * sp.exp(x1 * tt) + B * sp.exp(x2 * tt))

# visualization
##

fig = plt.figure()
ax = fig.subplots(1)
ax.plot(t, yy(t), label='analytical')
ax.plot(t, y[:, 1], 'x', label='numerical')
ax.legend()

##
assert(np.allclose(y[:, 1], yy(t)))
