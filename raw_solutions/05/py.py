import sys
import random

guess = False
lower = 0
upper = 300000000

def parse():
    arr = list(map(int, input().split()[1:]))
    alm = []
    input()
    for _ in range(7):
        input()
        l = []
        for line in sys.stdin:
            if line == '\n':
                break
            l.append(list(map(int, line.split())))
        alm.append(l)
    return arr, alm

def in_range(n, i, d):
    return i <= n < i+d

def reverse_convert(n, alm):
    for section in reversed(alm):
        #  print(n)
        #  print("section: ")
        #  print(section)
        for r in section:
            if in_range(n, r[0], r[2]):
                #  print(f"found {n} between {r[0]}, within {r[2]}, map by {r[1]-r[0]}")
                n += r[1] - r[0]
                break
    #  print(n)
    return n

def in_seeds(n, seeds):
    for i in range(0, len(seeds), 2):
        if in_range(n, seeds[i], seeds[i+1]):
            return True
    return False

arr, alm = parse()

min_loc = upper
for _ in range(1000000):
    loc = random.randint(lower, min_loc)
    l = reverse_convert(loc, alm)

    if in_seeds(l, arr) and loc < min_loc:
        print(loc)
        min_loc = loc

print("Last guess: " + str(min_loc))

for loc in range(min_loc, -1, -1):
    l = reverse_convert(loc, alm)
    if in_seeds(l, arr):
        print(loc)
