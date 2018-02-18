# INF-1101 - fei003 - a1
This report details the implementation of a a set, more specifically an *ordered set*, which was used as the underlying data structure for a "spam filter" program. The results of the implementations are also benchmarked and tested thorougly.

## 1. Implementation requirements
Some implementation details were given for the ordered set. The supported operations are:
1. Adding an element to the set.
2. Getting the current size of the set.
3. Checking wheter a specific element is contained in the set.
4. Getting the union of the set and another set.
5. Getting the intersection of the set and another set.
6. Getting the relative component set of the set.
7. Iterating over the elements of the set, in sorted order.
8. No upper bound on the number of elements that may be inserted into the set.

The assignment also stated that the performance analyzis of the seven supported operations, which can be different between multiple implementations, had to be documented in the report.

## 2. Theoretical background
<sup id="a1">[[1]](#f1)</sup> defines an abstract data type (ADT) as a data type whos operations are only accessed through an interface, and has its implementation hidden from the client (a program that uses an ADT). 
What this inherently means, is that the same set of operations can have several different implementations, and that the client can safely switch betweeen implementations without breaking existing code (as long as the contract of the interface is held).

In order to evaluate the effectivenes, or rather, the complexity of an algorithm, this report will use a mathematical notation called *Big O*. Big O is used  (in computer science) to classify an algorithms running time, or space requirements, as the input size increases. The mathematical definition will not be included in this report.

For implementing an ordered set as an ADT, an interface that described the operations with its return types and what not, was given in the precode (see [src/](./src/)).

## 3. Implementation
The rest is self-explanatory in the source code (which is well commented).

## 4. Design
The point of interest in the design was the `set_contains()` function, which was implemented using a standard __INSERTALGORITHMNAMEHERE_ algorithm. 

## 5. Discussion
In this section, the choices and the following consequences will be discussed. 

## 6. Conclusion
Something

## References
<b id="f1">1</b> Robert Sedgewick, 1997. Algorithms in C, Parts 1-4: Fundamentals, Data Structures,
Sorting, Searching: Fundamentals, Data Structures, Sorting, Searching. 3 Edition.
Addison-Wesley Professional.  [↩](#a1)

<b id="f1">2</b> http://something.org [↩](#a2)