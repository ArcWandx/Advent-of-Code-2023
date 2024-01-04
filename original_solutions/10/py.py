import sys

filename = "parsing"

def countI():
    f = open(filename, 'r')
    count = 0
    for line in f:
        for char in line:
            if char == 'I':
                count += 1
    print(count)


def find_space():
    f = open(filename, 'r')
    grid = []
    for line in f:
        grid.append(line)
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if grid[i][j] == 'I':
                for k in range(-1, 2):
                    for l in range(-1, 2):
                        if grid[i+k][j+l] == ' ':
                            print(i+k, j+l)

if __name__ == '__main__':
    countI()
    #  find_space()
