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

out = 0
cards = [1]
for line in sys.stdin:
    win, nums = parse(line)
    wins = count_wins(win, nums)

    # Append to the queue so that we have enough cards
    if len(cards) <= wins:
        cards += [1] * (wins - len(cards) + 1)

    # Current card
    n = cards.pop(0)
    out += n

    # Update the next cards
    for i in range(wins):
        cards[i] += n

print(out)
