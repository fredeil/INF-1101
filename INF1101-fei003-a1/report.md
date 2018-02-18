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

The assignment also stated that proper analyzis of the performance of the seven supported operations, which can be different between multiple implementations, had to be documented in the report.

## 2. Theoretical background
<sup id="a1">[[1]](#f1)</sup> defines an abstract data type (ADT) as a data type whos operations are only accessed through an interface, and has its implementation hidden from the client (a program that uses an ADT). 
What this inherently means, is that the same set of operations can have several different implementations, and that the client can safely switch betweeen implementations without breaking existing code (as long as the contract of the interface is held).

In order to evaluate the effectivenes, or rather, the complexity of an algorithm, this report will use a mathematical notation called *Big O*. Big O is used  (in computer science) to classify an algorithms running time, or space requirements, as the input size increases. The mathematical definition will not be included in this report.

For implementing an ordered set as an ADT, an interface that describes the operations with its return types and what not, were given in the precode handed out (see [src/](./src/)).

## 2. Implementation
The project is divided into 3 modules
1. Objects
   - ball.py
   - brick.py
   - pad.py
2. Scenes
   - scene.py
   - gamescene.py
3. Shared
   - constants.py
   - gameobject.py
   - vector2d.py

All the modules serves a purpose for the program:

1. Contains all object rendered on the screen (sprites)
2. Contains all scenes made for the game (e.g., menu, game, game over-scene)
3. Contains code share across all of the project

There are two reasons for doing it in this way, first one being; keeping a good structure (less clutter), and second one being; gathering classes with the same (underlying) purpose in one place.

All moving objects (sprites) utilizes the given Vector2D class for position and speed, respectively. 

The code itself is written in an object-oriented matter, with well defined and documented classes. So adding new features (scenes, objects, etc.) should be no problem at all in the future. 
Some limitations were found in the Vector2d class that was given. Therefore, a few lines of code were added to the class to better replicate methods found in other Vector2 classes. 

The sprites/gameobjects uses the built in collision detection in pygame (it was proven to be good enough for this project). The code for collision resolution was ommited because it was not perfected to an extent of satisfaction, hence, only the y-component of the speed vector is changed when a collision is detected between objects.

The game loop referred to in section #2 is partly defined in breakout.py and in the gamescene, this is because different scenes can draw and update different objects. this means that different scenes can be injected in the main game loop at run time.

The rest is self-explanatory in the source code (which is well commented).
## 3. Design

## 4. Conclusion
Altough the game is working, it is by no means perfect. There was complications in implementing proper collision resolution between object (which is was that part was omitted)

Missing implementations based on the requirements from section #1:

3. ~~The ball should bounce in a different direction based on where on the pad it hits~~

The report itself is also lacking a bit, the UML-diagrams are missing because this report was written in Markdown on a phone whilst commuting.

## References
<b id="f1">1</b> Robert Sedgewick, 1997. Algorithms in C, Parts 1-4: Fundamentals, Data Structures,
Sorting, Searching: Fundamentals, Data Structures, Sorting, Searching. 3 Edition.
Addison-Wesley Professional.  [↩](#a1)

<b id="f1">2</b> http://www.pygame.org/wiki/about [↩](#a2)