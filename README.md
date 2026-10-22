# Polish Calc

Reverse Polish notation calculator.

Just something to make quick-math in console for things like Factorio with FORTH-like syntax.

This one is intresting because, unlike the "calculators" that you make
in programming class, this one has multiple ways to represent a number.
Also pretty nice usage in bash scripts.

Included are some basic functions for stack manipulation, sums and trigonometry.

## This is not state-of-the-art programming

I had a problem - needed a faster way to do math in console than with python - and this is
the on-knee solution. I know there are *cleaner* ways to implement this however:

"Bo neni cas pyco"
- Sobotka

# Building

If you can run g++ in Linux you should be fine.

On Windows you're on your own.

# Usage

Add `pc` to `PATH` either by adding it to `~/.bashrc` or your `~/.local/bin/`.
Then you can use it interactively or from args.

To get basic help:

```bash
pc -h
pc help
```

or

```bash
pc # interactive
help
```

## Number types

*in this priority (low to high)*
> int               3
> over (a/b)        22/7
> double            3.14    20%

When adding 2 differnt types it will auto cast to the closest.

You can manually cast to any type:
> i - to int
> o - to over
> d - to double

## Stack

It's a stack look into [FORTH](https://www.forth.com/starting-forth/1-forth-stacks-dictionary/#The_Stack_Forth8217s_Workspace_for_Arithmetic).

## Examples

```bash
pc
2 2 +
.s
(ctrl+d) # send EOF - exits

pc 2 2 + . # prints to cout & exits
```

If you it's using args and no prints are requested, it will automatically print
the whole stack to cerr with `.s`.

```bash
pc 2 2 +
```

Sums:

```bash
pc 3 3 2 1 5 sum . # 15
```

Trigonometry (`asin(0.707 * (pi / 180))`):

```bash
pc 0.707 asin pi 180 / / . # 44.9913
```

To print with higher precision use `pNUM`:

```bash
pc 2 3 d / p8 # <1> 0.66666667
```

# License

Licensed under GPLv3 - see LICENSE
