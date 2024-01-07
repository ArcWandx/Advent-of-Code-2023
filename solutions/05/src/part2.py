import sys
import random

lower = 0
upper = 300000000
guesses = 500000

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
        for r in section:
            if in_range(n, r[0], r[2]):
                n += r[1] - r[0]
                break
    return n

def in_seeds(n, seeds):
    for i in range(0, len(seeds), 2):
        if in_range(n, seeds[i], seeds[i+1]):
            return True
    return False

arr, alm = parse()

for _ in range(guesses):
    loc = random.randint(lower, upper)
    l = reverse_convert(loc, alm)

    if in_seeds(l, arr):
        print(loc)
        upper = loc

print("Last guess: " + str(upper))

for loc in range(upper, lower-1, -1):
    l = reverse_convert(loc, alm)
    if in_seeds(l, arr):
        print(loc)
