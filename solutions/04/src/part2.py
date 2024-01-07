import sys
num_cards = int(sys.argv[1])

def parse(line):
    id = int(line.split(": ")[0].split()[1])
    win, nums = line.split(": ")[1].split(" | ")
    win = win.split()
    nums = nums.split()
    return id, win, nums

def count_wins(win, nums):
    count = 0
    for i in win:
        if i in nums:
            count += 1
    return count

# List of counts of all cards
cards = [1 for _ in range(num_cards+1)]
# There is no 0th card
cards[0] = 0
for line in sys.stdin:
    id, win, nums = parse(line)
    wins = count_wins(win, nums)

    # Add the scratch cards won
    for i in range(id+1, id+wins+1):
        cards[i] += cards[id]

print(sum(cards))
