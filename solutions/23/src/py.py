import sys
import copy

grid = []
for line in sys.stdin:
    grid.append(line.strip())

# returns the length of the longest path
sys.setrecursionlimit(100000)
def dfs(grid, r, c):
    grid = copy.deepcopy(grid)
    if grid[r][c] == '#':
        return -100
    if r == len(grid)-1 and c == len(grid[0])-2:
        return 0

    grid[r] = grid[r][:c] + '#' + grid[r][c+1:]

    n = grid[r-1][c]
    e = grid[r][c+1]
    s = grid[r+1][c]
    w = grid[r][c-1]

    n = dfs(grid, r-1, c) if n != 'v' else -100
    e = dfs(grid, r, c+1) if e != '<' else -100
    s = dfs(grid, r+1, c) if s != '^' else -100
    w = dfs(grid, r, c-1) if w != '>' else -100

    return 1 + max(n, e, s, w)

print(dfs(grid, 0, 1))
