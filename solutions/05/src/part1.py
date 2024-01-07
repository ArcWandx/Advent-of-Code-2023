import sys

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

def convert(n, alm):
    for section in alm:
        for r in section:
            if in_range(n, r[1], r[2]):
                n += r[0] - r[1]
                break
    return n

arr, alm = parse()

for i in range(len(arr)):
    arr[i] = convert(arr[i], alm)

print(min(arr))

