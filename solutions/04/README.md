# [Day 4](https://adventofcode.com/2023/day/4)

## Part 1

I first parse out the list of winning numbers, and the list of numbers scratched.
To do this, I first split on `": "`, and take the second half, then split along
`" | "`, then finally split by whitespace.

Then, it's a simple matter of counting which winning numbers are in the scratched
numbers by iterating over the winning numbers and linear searching. The linear
search could be avoided by using a set, although the actual speedup is trivial
due to the small size of the input.

Lastly, 2 raised to the power of one less than the number of matching numbers
is added to the total. Note that cards with no winning numbers should not contribute
to the total; in my original solution, I used a guard clause to filter out such
cases. However, it's also possible to simply truncate the power of two to an int.
Since no wins would give 0.5 points, this naturally becomes 0.

Run on my input using `make p1`.  
Run on the sample input using `make p1_test`.

## Part 2

My solution uses a list that tracks the exact number of each specific card. This
requires the total number of cards to be passed in as a command line argument, in
order to initialize the list with the proper number of cards. I then parse the
input, mutating the list, and sum the mutated list.

For each scratch card, I add the number of copies of the current scratch card to
the cards after it. Note that this requires knowing the index in the list of the
current card; I do this by also parsing out the ID, instead of discarding it like
in part 1 (though this can instead just be a variable that's incremented each loop).

Run on my input using `make p2`.  
Run on the sample input using `make p2_test`.

## Part 2 - Buffer

The list based approach has two major downsides: the number of cards in total must
be initially known, and it requires allocating a large chunk of memory. Both of
these issues can be solved using a queue-like structure. Note that this isn't a
queue due to the need for random access; thus, I will call it a buffer.

The buffer is initialized with the count of the first scratchcard. Then, as we
parse each line, the first element is dequeued and added to the sum, and each of
the next cards are increased by the number of copies of the dequeued card.

This concept is essentially lazy loading. Instead of having a large buffer containing
all the cards, we only append more cards to the buffer when the number of wins
requires us to increase numbers past the end of the buffer. This highlights one
advantage of the list-based solution: it's conceptually simpler, and thus a little
bit faster to code.

Note that the python implementation of list that I am using has an O(n) pop front.
This ultimately doesn't matter too much; the size of the queue never grows beyond
10.

Run on my input using `make p2_alt`.
Run on the sample input using `make p2_alt_test`.

## Rankings

    Part 1: 00:06:35, 1387th
    Part 2: 00:15:37, 1314th
