# Project Setup

## My Templates

I have two main languages: C++ and Python. Furthermore, I use a makefile to speed
things up when testing and debugging. By default, my programs are setup to take
standard input.

All of my templates were built over the course of Advent of Code, as I figured
out what was useful to me and what worked.

### Makefile

The first target in the makefile, `out`, is the compiled C++ binary. This
allows me to quickly compile by just typing `make`. In a similar vein, the
`clean` target allows me to trigger a recompile in the case that I compile
manually.

To run my program, I have two different targets depending on what language is used:
`run` is for C++ and `py` is for Python. Both targets expect the program to read
a file using redirection from standard input.

The `test` target by default in this template depends on the compiled C++ binary.
In all cases, I use it to run the sample input. On days where I think Python is
a better fit, I manually edit the target to instead be:

    test:
        python3 py.py < small

which runs the sample data with the python script instead. I chose not to have a
separate target for running the sample data, as having two different targets
depending on which language is used was confusing enough.  
In hindsight, it probably would have been more efficient to only have the `test`
and `run` targets, with different lines commented out for the different languages.

Depending on the day, two other common targets that I would add are `edit`, to quickly
open my editor in the case that the folder gets crowded, and `debug`, which compiles
with `-fsanitize=address` and `-g` for help with debugging memory errors.

### C++ Template

My template starts by including a few of the more commonly used STL packages, and
of course `using namespace std;`, as C++ will need all the syntax sugar it can get.

The syntax sugar continues with the next section of macros. To keep it simple, I
kept it down to only the most useful ones. Two for loops; one for iterating over
an entire length, and one for iterating over a range. There is also one added for
reverse iteration, though that ended up not being used. I also had a macro to get
the length and cast it to an `int`, since I compile with `-Wall`, and thus would
get a warning about comparing `int` and `size_t`.

I also defined a few shorthands for type names; all of them I think are fairly logical
and unambiguous. The only one that might be a bit odd is using `vec` for `vector`;
this was done as a compromise. There were several grid based days; instead of
permanently adding a `vector<string>` to my template, I instead opted to shorten
it.

Lastly, I have a few debugging tools. This mostly came in handy to run some function
a specific number of times, using the global `DEBUG_COUNT` variable to keep track.

### Python Template

Unlike the C++ template, which is a lot more complex, this one only does the bare
minimum of parsing standard input. The reasoning comes down to the fact that any
given day usually can be solved mainly by one Python package. Furthermore, the high
amount of syntax sugar in python makes the shorthands used for C++ unnecessary.

## My Workflow

Right before the start of a new day's challenge, I copy this folder to use as a
template. For example, to create the Day 1 project directory: `cp -r 0 01`.

Upon the release of the day's challenge, I immediately copy-paste the sample
input into a text file called `small`, and copy-paste my input into a textfile
called `input`. Both of these actions are done by hand; it takes ~5 seconds, so
it is not worth automating.

Next, I read the problem in its entirety. This usually takes too much time for
me to have shot at the global leaderboards, but this is fine by me; I think it's
better to get a complete understanding of the question from the get go, rather than
purely pursuing speed.

With the problem read, and the beginnings of a solution in my head, I choose a
language and start coding. I first ensure that my solution works on the input data,
and that there's no logical flaws I can find; then, I run my solution on my input.

Once I've solved both parts, I'll write my answers down to a text file called `answer`.
