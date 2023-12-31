import sys

grid = []
for line in sys.stdin:
    grid.append(line)

g = []
r = [True] * len(grid)
c = [True] * len(grid[0])

for i in range(len(grid)):
    for j in range(len(grid[i])):
        if grid[i][j] == '#':
            g.append([i, j])
            r[i] = False
            c[j] = False

for i in range(len(r) - 1, -1, -1):
    if r[i]:
        for p in g:
            if p[0] > i:
                #  p[0] += 1000000
                p[0] += 1
for i in range(len(c) - 1, -1, -1):
    if c[i]:
        for p in g:
            if p[1] > i:
                #  p[1] += 1000000
                p[1] += 1

sum = 0
for i in range(len(g)):
    for j in range(i + 1, len(g)):
        sum += abs(g[i][0] - g[j][0]) + abs(g[i][1] - g[j][1])

print(sum)
