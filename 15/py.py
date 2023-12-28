import sys

keys = [[] for _ in range(256)]
values = [[] for _ in range(256)]

def hash(s):
    out = 0
    for i in range(len(s)):
        out = (out + ord(s[i])) * 17 % 256
    return out

def equals(label, focus):
    h = hash(label)
    for i in range(len(keys[h])):
        if keys[h][i] == label:
            values[h][i] = focus
            return
    keys[h].append(label)
    values[h].append(focus)

def minus(label):
    h = hash(label)
    for i in range(len(keys[h])):
        if keys[h][i] == label:
            keys[h].pop(i)
            values[h].pop(i)
            return

def main():
    for line in sys.stdin:
        for sub in line.split(','):
            if '=' in sub:
                label, focus = sub.split('=')
                equals(label, int(focus))
            else:
                minus(sub[:-1])
            #  for i in range(4):
                #  print('Box', i)
                #  for key, value in zip(keys[i], values[i]):
                    #  print(' [', key, value, ']')
                #  print()

    print(sum([sum([(i+1)*(j+1)*n for j, n in enumerate(l)]) for i, l in enumerate(values)]))

if __name__ == '__main__':
    main()
