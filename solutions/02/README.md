# [Day 2](https://adventofcode.com/2023/day/2)

This day was mostly about input parsing. Python's `.split()` was therefore incredibly
useful.

To get the game ID, split on `':'`, then split on whitespace and take the second.  
To get each round of a game, split on `"; "`.  
For each round, to get the number and type of each cube drawn, split on `", "`.  
For each cube type, split on whitespace to get the count and color respectively.

## Part 1

Once you parse out the ID and counts-by-color for each game, you can simply check
that no color exceeds its respective max, and add the ID to a running sum as needed.

Run with `make p1`.

## Part 2

Now, for each game, keep track of the max number of each color. Once all rounds
have been processed, simply multiply them to calculate the color and add them.

Run with `make p2`.

## Rankings

    Part 1: 00:27:22, 6291st`
    Part 2: 00:31:17, 5478th
