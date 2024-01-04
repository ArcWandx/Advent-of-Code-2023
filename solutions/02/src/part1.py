import sys

sum = 0
max = {'red': 12,
       'green': 13,
       'blue': 14}
for line in sys.stdin:
    id, line = line.split(': ')
    id = int(id.split()[1])
    flag = True
    for round in line.split('; '):
        for draw in round.split(', '):
            count, color = draw.split()
            count = int(count)
            if count > max[color]:
                flag = False
                break
    if flag:
        sum += id

print(sum)

