import numpy as np
import algopy as alg
import matplotlib.pyplot as plt
from scipy import optimize

G = 6.67e-11
year = 3.15e7


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


def gravity(M1, x1, M2, x2):
    return G * M1 * M2 * (x2 - x1) / np.power(np.linalg.norm(x1 - x2), 3)


def km2au(km):
    return km * 6.68458712e-9


def au2km(au):
    return au * 1.496e8


def visualize(ax, state):
    ax[0].plot(state[:, 0], state[:, 1])
    ax[0].set_xlabel('x (m)')
    ax[0].set_ylabel('y (m)')
    ax[0].set_title('Position')
    ax[1].plot(state[:, 3], state[:, 4])
    ax[1].set_xlabel('$v_x (m)$')
    ax[1].set_ylabel('$v_y (m)$')
    ax[1].set_title('Velocity')


AU = au2km(1) * 1000
sun = Particle()
sun.m = 1.9885e30
sun.x = np.array([0.0, 0.0, 0.0])
sun.v = np.array([0.0, 0.0, 0.0])
earth = Particle()
earth.m = 5.972e24
earth.x = np.array([AU, 0, 0])
earth.v = np.array([0, 35000.0, 0])
jupiter = Particle()
jupiter.m = 1.898e28
jupiter.x = np.array([4.53549236092 * AU, 0, 0])
jupiter.v = np.array([0, 13070.0, 0])


def earth_forcing(x):
    return gravity(earth.m, x, sun.m, sun.x) + \
        gravity(earth.m, x, jupiter.m, jupiter.x)


def earth_forcing_jac(x):
    ax = alg.UTPM.init_jacobian(x)
    return alg.UTPM.extract_jacobian(earth_forcing(ax))


def jupiter_forcing(x):
    return gravity(jupiter.m, x, sun.m, sun.x) + \
        gravity(jupiter.m, x, earth.m, earth.x)


def jupiter_forcing_jac(x):
    ax = alg.UTPM.init_jacobian(x)
    return alg.UTPM.extract_jacobian(jupiter_forcing(ax))


##
earth.f = earth_forcing
earth.jac = earth_forcing_jac
jupiter.f = jupiter_forcing
jupiter.jac = jupiter_forcing_jac
dt = 0.005 * year
t = 0
time = [t]
while (t < 100 * year):
    earth.leapfrog(dt)
    jupiter.leapfrog(dt)
    # earth.semi_implicit_euler(dt)
    # jupiter.semi_implicit_euler(dt)
    # earth.explicit_implicit_euler(dt)
    # jupiter.explicit_implicit_euler(dt)
    # earth.implicit_euler(dt)
    # jupiter.implicit_euler(dt)
    t += dt
    time.append(t)


time = np.array(time)
earth_state = np.array(earth.state).reshape(-1, earth.N)
jupiter_state = np.array(jupiter.state).reshape(-1, jupiter.N)
sun_state = np.array(sun.state).reshape(-1, sun.N)

fig = plt.figure()
ax = fig.subplots(1, 2)  # figsize=(15, 5)
visualize(ax, sun_state)
visualize(ax, earth_state)
visualize(ax, jupiter_state)
##
