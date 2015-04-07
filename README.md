## Constant Execution Time (CET) sorting

Some C implementations of standard and CET versions of different sorting algorithms to sort 10000 integers. A constant execution time guarantee can be useful in certain real-time systems. These implementations are intended purely as experiments to see how different CET sorting algorithms behave for worst-case, best-case and random input in terms of overhead and execution time.

### Usage

`constant_sorts [sort_type] [v] [w|b|r]`

Where `sort_type` can be any of:

```
b | c (bubblesort    | CET bubblesort)
i | j (insertionsort | CET insertionsort)
q     (quicksort)
s | t (selectionsort | CET selectionsort)
y | z (shellsort     | CET shellsort)
```

Flag `v` enables verbose reporting. `w | b | r` for generating worst-case (reverse-sorted), best-case (sorted) or random (default) sets of integers.

### Results

A short paper on the results can be found [here](http://ktslabbie.github.io/resources/papers/2011_Constant_Time_Algorithms.pdf).
