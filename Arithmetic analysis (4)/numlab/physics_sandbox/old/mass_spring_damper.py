import numpy as np
import algopy as alg
import matplotlib.pyplot as plt
from scipy import optimize


class Particle:

    def __init__(self):
        self.m = 0.0
        self.x = np.array([0.0, 0.0, 0.0])
        self.v = np.array([0.0, 0.0, 0.0])
        self.f = None
        self.jac = None
        self.state = []
        self.N = 6

    def explicit_implicit_euler(self, dt):
        a = self.f(self.x) / self.m
        self.x += self.v * dt
        self.v += a * dt
        self.state.append([self.x.copy(), self.v.copy()])

    def semi_implicit_euler(self, dt):
        a = self.f(self.x) / self.m
        self.v += a * dt
        self.x += self.v * dt
        self.state.append([self.x.copy(), self.v.copy()])

    def leapfrog(self, dt):
        an = self.f(self.x) / self.m
        self.x += self.v * dt + 0.5 * an * np.power(dt, 2)
        ann = self.f(self.x) / self.m
        self.v += 0.5 * (an + ann) * dt
        self.state.append([self.x.copy(), self.v.copy()])

    def implicit_euler(self, dt):
        def func(x):
            f = self.f(x) / self.m
            return x - f * dt * dt - dt * self.v - self.x

        def func_jac(x):
            jac = self.jac(x) / self.m
            return 1 - jac * dt * dt

        root = optimize.root(func, self.x, jac=func_jac, tol=1e-10)

        self.v += self.f(self.x) / self.m * dt
        self.x = root.x
        self.state.append([self.x.copy(), self.v.copy()])


def visualize(ax, state):
    ax.plot(state[:, 1], state[:, 4])
    ax.set_xlabel('$y (m)$')
    ax.set_ylabel('$v_y (m)$')
    ax.set_title('State-Space')


k = 1000
g = np.array([0, -9.8, 0])
m = 100
x0 = -5.0
system = Particle()
system.m = m
system.x = np.array([0, x0, 0])
system.v = np.array([0, 0.0, 0])


def forcing(x):
    return g * m - k * x


def forcing_jac(x):
    ax = alg.UTPM.init_jacobian(x)
    return alg.UTPM.extract_jacobian(forcing(ax))


system.f = forcing
system.jac = forcing_jac
dt = 0.01
t = 0
time = [t]
while (t < 10):
    # system.semi_implicit_euler(dt)
    # system.leapfrog(dt)
    # system.explicit_implicit_euler(dt)
    system.implicit_euler(dt)
    t += dt
    time.append(t)


time = np.array(time)
state = np.array(system.state).reshape(-1, system.N)

fig = plt.figure()
ax = fig.subplots(1, 1)  # figsize=(15, 5)
visualize(ax, state)
