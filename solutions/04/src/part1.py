import sys

def parse(line):
    win, nums = line.split(": ")[1].split(" | ")
    win = win.split()
    nums = nums.split()
    return win, nums

def count_wins(win, nums):
    count = 0
    for i in win:
        if i in nums:
            count += 1
    return count

sum = 0
for line in sys.stdin:
    win, nums = parse(line)
    wins = count_wins(win, nums)

    sum += int(2 ** (wins - 1))

print(sum)
