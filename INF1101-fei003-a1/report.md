# INF-1101 - fei003 - a1
This report details the implementation of a replication of the well-known Arcade game named **Breakout**, which was originally developed and published by Atari, Inc. in 1973 <sup id="a1">[1](#f1)</sup>. 

The underlying intent of the project is to utilize object-oriented design by exploring OOP concepts such as classes, inheritance, polymorphism in order to solve a software problem.

## 1. Implementation requirements
The requirements for the code were as following (taken directly from the assignment):

1. Implement the game in accordance to object-oriented design,
2. The platform (pad) should be controlled by the mouse or keyboard,
3. The ball should bounce in a different direction based on where on the pad it hits,
4. A brick disappears when a ball hits it,
5. The ball bounces off the walls, angle in = angle out,
6. The game is won when all bricks are removed, the game is lost when the ball its the bottom of the screen.

There were also examples on extra features to implemented (e.g., more levels, high score list, sound, etc.). 

For more information about technological requirements/prerequisites refer to the [README.md](./src/README.md) file in the `src/` directory.


## 2. Theoretical background
For implementing the game, various OOP concepts were used such as inheritance, "encapsulation" and polymorpism. By utilizing these concepts much of the code is written once an reused other places in the code, which is the idea behind OOP.

The programming language used in this project was Python, which is an interpreted high-level programming language well suited for object oriented design.

For speeding up the development process a python module/library called __Pygame__ is used, pygame is an highly portable, cross-platform open-source library for making multimedia applications such as games <sup id="a2">[2](#f2)</sup>.

The pygame documentation states that games run in a fixed pattern, which continously does these four tasks (often reffered to as the game loop):

1. Poll and handle events (e.g., user events, time, etc.)
2. Update game elements (e.g., remove objects, update positions)
3. Draw current state to the surface 
4. Display the surface 

## 3. Implementation
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

## 4. Conclusion
Altough the game is working, it is by no means perfect. There was complications in implementing proper collision resolution between object (which is was that part was omitted)

Missing implementations based on the requirements from section #1:

3. ~~The ball should bounce in a different direction based on where on the pad it hits~~

The report itself is also lacking a bit, the UML-diagrams are missing because this report was written in Markdown on a phone whilst commuting.

## References
<b id="f1">1</b> https://www.atari.com/history/1972-1984-0 [↩](#a1)

<b id="f1">2</b> http://www.pygame.org/wiki/about [↩](#a2)