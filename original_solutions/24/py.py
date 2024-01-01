import sys
from z3 import *

class Hail:
    def __init__(self, px, py, pz, vx, vy, vz):
        self.px = px
        self.py = py
        self.pz = pz
        self.vx = vx
        self.vy = vy
        self.vz = vz

hails = []
for line in sys.stdin:
    pos, vel = line.split(" @ ")
    px, py, pz = pos.split(", ")
    vx, vy, vz = vel.split(", ")
    hails.append(Hail(px, py, pz, vx, vy, vz))

t1 = Int('t1')
t2 = Int('t2')
t3 = Int('t3')
px = Int('px')
py = Int('py')
pz = Int('pz')
vx = Int('vx')
vy = Int('vy')
vz = Int('vz')

s = Solver()
s.add(t1 >= 0)
s.add(t2 >= 0)
s.add(t3 >= 0)

h1 = hails[0]
h2 = hails[1]
h3 = hails[2]

s.add(h1.px + h1.vx * t1 == px + vx * t1)
s.add(h1.py + h1.vy * t1 == py + vy * t1)
s.add(h1.pz + h1.vz * t1 == pz + vz * t1)

s.add(h2.px + h2.vx * t2 == px + vx * t2)
s.add(h2.py + h2.vy * t2 == py + vy * t2)
s.add(h2.pz + h2.vz * t2 == pz + vz * t2)

s.add(h3.px + h3.vx * t3 == px + vx * t3)
s.add(h3.py + h3.vy * t3 == py + vy * t3)
s.add(h3.pz + h3.vz * t3 == pz + vz * t3)

# print the variables
print(s.check())
print(s.model())

