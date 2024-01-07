# [Day 5](https://adventofcode.com/2023/day/5)

While this day looks like you should be using maps, the ranges unfortunately mean
that maps are impractical.

## Part 1

An array is used to store the seeds, and a list of lists of lists is used to store
the almanac information. Each of the seven lists of lists is used to store the
information of one map, and each list in them directly stores one line of the input.
The core of my solution to part 1 iterates over the array of seeds, converting them
using the almanac, and finds the minimum.

In order to convert a given seed number to a location using the almanac, I iterate
through each of the seven sections of the almanac. In each section, I check if the
number is in the range of each line, and if it is, I change the number by the
difference between the destination and source range starts. I do this by iterating
through all the lines in the section, making the assumption that the number shows
up in at most one section. This method also leaves the number untouched if it is
not in a range, as required.

Run on my input using `make p1`.  
Run on the sample input using `make p1_test`.

## Part 2

We now need to convert locations into seeds. This is done by pretty much reversing
the steps to convert from seeds to locations. I iterate backwards through the
sections of the almanac, and increase by the negation of the delta used for the
forward conversion if the number is in the range.

In addition, we need the ability to check if a given number is a seed. This could
be done using a sorted associative array, which would allow binary searching for
the start of the range. However, this is somewhat overkill, given the small number
of seed ranges given. Instead, I use a linear search, which has the benefit that
I can parse the input in the same way as I did for part 1.

Just reverse conversion and checking if a number is a seed is enough to brute force.
This is what I started with; however, as expected it is far too slow.

My final algorithm uses a "guess and check" method. An upper and lower bound is
manually configured, and the program randomly guesses a location between the upper
and lower bounds, updating the upper bound if the random location corresponds to
a seed. It does this for a configured number of guesses, which gets fairly close
to the true answer. Then, starting from known upper bound, the program iterates
backwards, printing out any locations that corresponds to seeds that it finds.

This approach heavily relies on the assumption that a guessing algorithm can get
close enough to the true answer. Luckily, this is true for the given input. However,
it's not impossible that some specific input has a single seed that maps to a very
low location, in which case this approach would devolve into a reverse brute-force.
Similarly, if the initial upper bound is too high, the program also devolves into
a reverse brute-force.

Run on my input using `make p2`.  
Run on the sample input using `make p2_test`.

## Alternative Solution - Part 2

A more mathematically sound approach would be to map each range of seeds to ranges
of locations. Each line of each section would cause one or more ranges to split.
A similar approach is needed for part 2 of Day 19.

## Rankings

    Part 1: 01:03:01, 8140th
    Part 2: 02:02:09, 4449th
