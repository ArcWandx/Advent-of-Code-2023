# Day 1

## Part 1

I used a simple linear search, remembering the first integer encountered, and the
most recent integer encountered. At the end of the linear search, the most recent
integer encountered is the last integer in the string.

Lastly, on each line, each pair of digits is converted to a number by multiplying
the first digit by 10 and adding the last digit, and the number found is added to
a running sum, which is finally printed out.

Run using `make p1`.

## Part 1 - Two-ended linear search

Instead of doing a full linear search of the line, we could find the first
integer iterating forwards, then find the last integer by finding the first
integer when iterating backwards.

This runs faster overall; however, this speedup is dependant on the length of each
line. Since the longest line is still only 52 characters long, this ultimately is
a negligible speedup. However, the logic may be easier to follow.

Run using `make p1_two`.

## Part 1 - Regex

We can use a regular expression to find the first and last integers. Here are
the regexes:

    first: ^.*?(\d)
    last:  .*(\d).*?$

Both regexes search for a digit (`\d`), relative to an anchor (`^` for the start,
`$` for the end). The wildcards (`*`) match ungreedily (`?`), resulting in the closest
digit to each anchor being captured.

We can use the capture groups to do a find-and-replace, converting each line into
a single number. I will do it in vim. Note that because the first digit is sometimes
also the last digit, you must first duplicate each digit:

    :%s/\v(\d)/\1\1/g

(find `(\d)`, putting it in a capturing group, and replace it with two copies of
what is captured).  
Next, use the two regexes in tandem to extract the first and last digit, and
remove everything else on the line:

    :%s/^.\{-}\(\d\).*\(\d\).*$/\1\2/g

Now that everything has been reduced to numbers, add them. My preferred way of doing
this is to append a "`+`", and run it through python:
`gg$\<C-v>GkA +\<Esc>VGJyy`, open python, paste.

(I know it's possible to do it with `<C-r>=`, but it's a lot slower.)

## Part 2

My solution used a simple modification of my part 1. I added a function that
checked if the substring at any given index spelled out a digit. Then, I first
check if the current index of the line spells out a digit. If it does not, I check
if the current position contains a digit character. If both checks fail, then I
skip the current index. Otherwise, like in part 1, I find the first and last integers.

Run using `make p2`.

## Part 2 - Find-and-replace

Instead of writing additional logic to handle spelt numbers, we instead use a
find-and-replace in a text editor, e.g. replacing "one" with "o1ne". We do it
in this manner to avoid breaking up groups that share letters. For example,
"oneight" contains both a 1 and an 8, but replacing "one" with "one1" would cause
the find and replace to not replace the 8.

Run using `make p2_alt`.
