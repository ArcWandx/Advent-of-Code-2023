import sys

sum = 0
for line in sys.stdin:
    id, line = line.split(': ')
    id = int(id.split()[1])
    max = {'red': 0,
           'green': 0,
           'blue': 0}
    for round in line.split('; '):
        for draw in round.split(', '):
            count, color = draw.split()
            count = int(count)
            if count > max[color]:
                max[color] = count
    power = max['red'] * max['green'] * max['blue']
    sum += power

print(sum)

