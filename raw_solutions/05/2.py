import sys
import random

guess = False
lower = 125700000
upper = 160000000

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

arr, alm = parse()
#  print(alm)

loc = lower
min_loc = -1
min = 300000001
for _ in range(10000000):
    #  loc = random.randint(0, 300000000) # initial
    if (guess):
        loc = random.randint(lower, upper)
    #  print(f"loc: {loc}")
    l = reverse_convert(loc, alm)

    for i in range(0, len(arr), 2):
        if in_range(l, arr[i], arr[i+1]):
            if (guess):
                if loc < min_loc:
                    min_loc = loc
            else:
                print(loc)
                sys.exit(0)
    loc += 1
    if loc % 100000 == 0:
        if (guess):
            print(min_loc)
        else:
            print(loc)

print(min_loc)

