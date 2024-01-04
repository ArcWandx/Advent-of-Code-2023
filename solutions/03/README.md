# [Day 3](https://adventofcode.com/2023/day/3)

This day is the first day that I started saving the sample input. You can
run the solutions on the sample input using `make p1_test` and `make p2_test`.

There are a few different ways to solve this, but I will only be detailing the
method I used.

## Part 1

The core idea for most solutions is to group the numbers into blocks. My first
attempt at this used a grid of structs that each contained an int; this was
ultimately rather complex and resulted in memory errors everywhere. My final,
successful attempt used pointers to `int`s. By having each block be represented
by one integer in memory, I could add the pointers to a set to easily filter out
duplicates.

I iterate over the grid 3 times.
1. The first time, I fill out a grid of integer pointers. I iterate along each
row; whenever a digit is encountered, I append it to the current number. Once we
reach a non-digit, I backtrack, setting the previous blocks to point to the
number that was found, and set the current number to a newly allocated 0.

2. On the second iteration, I fill out a grid of sets of integer pointers. This
keeps track of what numbers are next to each part. Everytime that a part is
encountered, the 3x3 square around it is searched for numbers, and any numbers
found are added to the part's set of numbers. This conveniently avoids duplicates,
since multiple pointers to the same integer won't be added.

3. The final iteration over the grid tallies all the part numbers. In my
implementation, the integer pointers are added to a set to avoid duplicates. In
practice, however, this turns out to be unnecessary, as all part numbers uniquely
belong to a single part due to how the input is generated. Thus, a simple summation
would suffice.

## Part 2

My first iteration over the grid is the exact same.

In my second iteration over the grid, I instead check for gears (`'*'`) specifically,
though in practice this is a pretty trivial speedup and makes no real difference.

In my third iteration over the grid, I instead check for gears with exactly two
numbers. I multiply the two numbers to find the gear ratio and sum the ratios.

## Rankings

Unfortunately, I originally missed this day, and had to go back to it afterwards.
I gave up around the 80 minute mark, and looked at someone else's solution. That's
why the template used is so much more advanced than both Day 2 and Day 4.  
Coincidentally, this is also where the idea of for loop macros came from.

