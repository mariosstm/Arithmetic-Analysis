#!/usr/bin/env python2

import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as sp
from physics import System, Particle


def visualize(ax, state):
    ax[0].plot(state[:, 0], state[:, 1], 'o')
    ax[0].set_xlabel('$q_x (m)$')
    ax[0].set_ylabel('$q_y (m)$')
    ax[0].set_title('Position')
    ax[1].plot(state[:, 3], state[:, 4], 'x')
    ax[1].set_xlabel('$u_x (m)$')
    ax[1].set_ylabel('$u_y (m)$')
    ax[1].set_title('Velocity')


def km2au(km):
    return km * 6.68458712e-9


def au2km(au):
    return au * 1.496e8


def gravity(M1, x1, M2, x2):
    return G * M1 * M2 * (x2 - x1) / np.power(np.linalg.norm(x1 - x2), 3)


AU = au2km(1) * 1000
G = 6.67e-11
year = 3.15e7
sunMass = 1.9885e30
earthMass = 5.972e24
jupiterMass = 1.898e28

system = System()
sun = Particle(sunMass)
system.addComponent(sun)
earth = Particle(earthMass)
system.addComponent(earth)
jupiter = Particle(jupiterMass)
system.addComponent(jupiter)

state = system.initializeState()
earth.setQ(state, np.array([AU, 0, 0]))
earth.setU(state, np.array([0, 35000.0, 0]))
jupiter.setQ(state, np.array([4.53549236092 * AU, 0, 0]))
jupiter.setU(state, np.array([0, 13070.0, 0]))

earth.applyForce(lambda state:
                 gravity(earth.m, earth.getQ(state),
                         sun.m, sun.getQ(state)) +
                 gravity(earth.m, earth.getQ(state),
                         jupiter.m, jupiter.getQ(state)))
jupiter.applyForce(lambda state:
                   gravity(jupiter.m, jupiter.getQ(state),
                           sun.m, sun.getQ(state)) +
                   gravity(jupiter.m, jupiter.getQ(state),
                           earth.m, earth.getQ(state)))


def dydt(y, t):
    """
    """
    system.setFromY(state, y)
    return system.getYDot(state)


t = np.linspace(0, 2 * year, 100)
y0 = system.getY(state)
y = sp.odeint(dydt, y0, t)

fig = plt.figure()
ax = fig.subplots(1, 2)
visualize(ax, y[:, 0:6])
visualize(ax, y[:, 6:12])
visualize(ax, y[:, 12:18])
