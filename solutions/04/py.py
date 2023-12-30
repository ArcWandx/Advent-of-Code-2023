import sys
#  num_cards = 6
num_cards = 204

out = 0
cards = [1 for _ in range(num_cards+1)]
cards[0] = 0
for line in sys.stdin:
    id = int(line.split(": ")[0].split()[1])
    win, nums = line.split(": ")[1].split(" | ")
    win = win.split()
    nums = nums.split()

    # Part 1
    count = 0
    for i in win:
        if i in nums:
            count += 1
    if count == 0:
        continue
    out += 2 ** (count - 1)

    # Part 2
    for i in range(id+1, id+count+1):
        cards[i] += cards[id]

print(out)
print(sum(cards))
