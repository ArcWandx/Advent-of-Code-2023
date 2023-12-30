import sys

dir = []
for line in sys.stdin:
    #  dir.append(line.split()[:2])
#  dir = [[a, int(b)] for a, b in dir]
    dir.append(line.split()[2])
dir = [[s[2:7], s[7]] for s in dir]
dir = [[int(s[0], 16), int(s[1])] for s in dir]
dir = [[b, a] for a, b in dir]

digger = (0, 0)
corners = []
perimeter = 0
for a, b in dir:
    corners.append(digger)
    perimeter += b
    new_digger = digger
    match a:
        #  case 'R':
        case 0:
            new_digger = (digger[0] + b, digger[1])
        #  case 'D':
        case 1:
            new_digger = (digger[0], digger[1] - b)
        #  case 'L':
        case 2:
            new_digger = (digger[0] - b, digger[1])
        #  case 'U':
        case 3:
            new_digger = (digger[0], digger[1] + b)
    digger = new_digger

# shoelace + pick's
area = 0
for i in range(len(corners)):
    x1, y1 = corners[i]
    x2, y2 = corners[(i+1)%len(corners)]
    area += (x1*y2 - x2*y1)
area = abs(area) // 2

lattice = area + perimeter//2 + 1

print(lattice)
