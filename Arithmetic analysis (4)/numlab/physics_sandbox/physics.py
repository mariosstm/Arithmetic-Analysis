import numpy as np
# import algopy as alg
from functools import reduce

def mapFunOnArgAndSum(arg, functionList):
    """Map functions on argument and sum results.
    """
    return reduce(lambda x, y: x + y, map(lambda x: x(arg), functionList))


class State:
    """
    """

    def __init__(self, t, nq, nu):
        """
        """
        self.t = t
        self.q = np.zeros(nq, np.double)
        self.u = np.zeros(nu, np.double)


class StateComponent:
    """
    """

    def __init__(self):
        """
        """
        self.nq = None
        self.nu = None
        self.qIndex = None
        self.uIndex = None
        self.forcingList = None

    def applyForce(self, forcingFunction):
        """
        """
        self.forcingList.append(forcingFunction)

    def setQ(self, state, q):
        """
        """
        assert(self.nq == q.shape[0])
        state.q[self.qIndex:self.qIndex + self.nq] = q

    def setU(self, state, u):
        """
        """
        assert(self.nu == u.shape[0])
        state.u[self.uIndex:self.uIndex + self.nu] = u

    def getQ(self, state):
        """
        """
        return state.q[self.qIndex:self.qIndex + self.nq]

    def getU(self, state):
        """
        """
        return state.u[self.uIndex:self.uIndex + self.nu]


class Particle(StateComponent):
    """
    """

    def __init__(self, mass):
        """
        """
        self.nq = 3
        self.nu = 3
        self.m = mass
        self.forcingList = [lambda state: np.zeros(self.nu)]

    def getQDot(self, state):
        """
        """
        return self.getU(state)

    def getUDot(self, state):
        """
        """
        f = mapFunOnArgAndSum(state, self.forcingList)
        return f / self.m


class System:
    """
    """

    def __init__(self):
        """
        """
        self.lastQIndex = 0
        self.lastUIndex = 0
        self.stateComponents = []

    def addComponent(self, component):
        """
        """
        component.qIndex = self.lastQIndex
        component.uIndex = self.lastUIndex
        self.lastQIndex += component.nq
        self.lastUIndex += component.nu
        self.stateComponents.append(component)

    def initializeState(self):
        """
        """
        return State(0, self.lastQIndex, self.lastUIndex)

    def getY(self, state):
        """
        """
        y = []
        for c in self.stateComponents:
            y.append(c.getQ(state))
            y.append(c.getU(state))

        return np.array(y).reshape(-1,)

    def setFromY(self, state, y):
        """
        """
        assert(self.lastQIndex + self.lastUIndex == y.shape[0])
        baseIndex = 0
        for c in self.stateComponents:
            nq = c.nq
            nu = c.nu
            c.setQ(state, y[baseIndex:baseIndex + nq])
            c.setU(state, y[baseIndex + nq:baseIndex + nq + nu])
            baseIndex += nq + nu

    def getYDot(self, state):
        """
        """
        yDot = []
        for c in self.stateComponents:
            yDot.append(c.getQDot(state))
            yDot.append(c.getUDot(state))

        return np.array(yDot).reshape(-1,)
