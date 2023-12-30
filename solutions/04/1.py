import sys

sum = 0
for line in sys.stdin:
    win, nums = line.split(": ")[1].split(" | ")
    win = win.split()
    nums = nums.split()
    count = 0
    for i in win:
        if i in nums:
            count += 1
    if count == 0:
        continue
    sum += 2 ** (count - 1)

print(sum)
