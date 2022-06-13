# Compression using combinatorics

video explanation: https://www.youtube.com/watch?v=NiGEva49bTE

By taking the order out of a set of numbers the set of numbers can be compressed.
The issue is finding a way to reorder the set that compliments the number of free bits from taking the order out

## EX:
3 bytes can be represented as 256 ^3 or 2 ^24.
With this combination you have 16777216 possible numbers 16777215, being the highest and 0 being the lowest.
When taking the order out you now have 2829056 possible numbers, 2829055 being the highest and 0 the lowest.
You can represent the highest number in bits with log(2829055)/log(2) rounded up: 22.
By taking the order out of the set, you now need 2 fewer bits to represent the set but need a way to reorder the set.

## Attempts at reordering
I've used something I call difference triangles where you have a permutation of numbers and write the difference of the numbers above, then the difference of those numbers above.
You do this until you have a triangle.
I would send the sides of the triangles as unordered sets and have the decompressor figure out the order.
This was unsuccessful because there were multiple triangles for given sets.

I then tried indexing prime numbers.
If the value you were trying to compress was 6, you would take the prime factors and then index them.
Prime factors of 6 are 2 and 3: 2 is the first(0th) prime, and 3 is the second(1st) prime.
You would compress the indexes of the prime numbers, in this case, 0 and 1, and send them.
The decompressor would decompress and have a 0 and 1. 
It would then get the appropriate primes and either multiply or add them.
I tried both and neither was feasible, primes don't grow fast enough.

Currently, I am trying to use Pascal's triangle for indexing.
The indexing is similar to the primes, but what they evaluate to are values on Pascal's triangle.
I find a combination of numbers that add up to what you are trying to compress and send the indexes of those numbers.
This seems more promising, but I have not found a size of Pascal's triangle(how many layers) and count of numbers chosen from it that work for a positive compression.

## What the solution seems to be
The solution seems to be a perfectly non-linear function/array of numbers that can be selected from and added up.
Pascal's triangle is currently my best bet, but with a size and selection count that may work you need a supercomputer to compress.
Decompression is much faster than compression.

## Compilation
Most file require "MyArr.h", and gnu multi precision(gmp).
Most files are individual files with their own main.
Compile with
```
g++ file.cpp -lgmp -lgmpxx
```

