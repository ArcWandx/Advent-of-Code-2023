import sys

arr = list(map(int, input().split()[1:]))
alm = []

def parse(alm):
    input()
    for _ in range(7):
        input()
        l = []
        for line in sys.stdin:
            if line == '\n':
                break
            l.append(list(map(int, line.split())))
        alm.append(l)
    return alm

def in_range(n, i, d):
    return i <= n < i+d

def convert(n, alm):
    for section in alm:
        #  print(n)
        #  print("section: ")
        #  print(section)
        for r in section:
            if in_range(n, r[1], r[2]):
                #  print(f"found {n} between {r[1]}, within {r[2]}, map by {r[0]-r[1]}")
                n += r[0] - r[1]
                break
    #  print(n)
    return n

alm = parse(alm)
#  print(alm)

for i in range(len(arr)):
    arr[i] = convert(arr[i], alm)

print(min(arr))

