# [Day 6](https://adventofcode.com/2023/day/6)

I solved this day entirely in desmos. Copy-paste the contents of `desmos.txt` into
[desmos](https://www.desmos.com/calculator). *n* is the distance, *k* is the time,
and *a* is a slider with bounds of 0 to √*n* and step size 1. Increase the value
of *a* until *ab* is just barely greater than *n*; that is, *ab - n* is just barely
positive. The number of ways to win is equal to *b* - *a* + 1.

## Part 1

*a* represents the number of seconds that the button is held down for. *b*, therefore,
is the amount of time that the boat spends moving. The total distance is thus *ab*.
We win if our total distance is greater than the largest recorded distance for each
race. Note that by the transitive property of multiplication, we can switch *a*
and *b*. So, the largest value of *a* that wins is the value of *b* for the smallest
value of *a* that wins. Then, the number of ways to win is the amount of
numbers between the smallest and largest values of *a* that win, or *b* - *a* + 1.

I chose to compute each of the numbers by hand, as there were only four races.

## Part 2

The solution for part 2 is roughly the same. Since the numbers are larger, you may
find it easier to first use a large step size for *a* before dialing it in.

I also wrote a python program that automates this process; the math is exactly the
same. Run it using `python part2.py`.

## Rankings

    Part 1: 00:09:19, 2336th
    Part 2: 00:15:39, 3082nd
