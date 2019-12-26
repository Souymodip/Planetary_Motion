# Planetary_Motion

---------------------------------- Description -------------------------------

1. A view of our solar system, as defined by Newtonian Mechanics.
2. The program is written in openGL(C++ / linux).
3. The program is meant for teaching children on how celestial objects behave in space.
4. Observe not only how the planet's trajectory is effected by the massive star, but also observe the interaction between planets and it combined effect on the motion of the star.
5. Changing the program code is very simple, and complex model of planetary system can be build, by varying number of planets, mass of each planet, even the gravitational constant can be tinkered with for observing its affect on the mechanics.
6. You will quickly realize that minute changes in any values drastically affect the mechanics of the system. If the distance is too far or gravitational constant is too small, planets will easily leave their orbits. It is actually quite hard to build a well behaving planetary system.
7. Use keys 'a', 'w', 'd', 's' for moving the camera, and 'z' and 'c' for zooming. Press 'r' to reset the camera position. 'i' and 'k' to look up and down, and 'j' and 'k' to look left or right.




----------------------------------- compiling --------------------------------

1. The code is tested for linux operating system.
2. Libraries freeglut.h and gl.h are necessary and should be stored in a folder include\GL.
3. Run the following command
4. 
   - g++ -O0 -g3 -Wall -c -fmessage-length=0 -o planets.o "./Celes.cpp" 
   - g++ -o planets planets.o -lGLU -lGL -lglut
   - or type $ make
   - Type $ ./planets

5. Double click planets (or type - ./planet)



---------------------------------- Editing ----------------------------------- 

1. The files fist.cpp and basic_shape.h contains core of the implementation.
2. For start, just open the file "initializer.h". Follow the simple instruction to create your own planet systes and compile and run.
3. A running example is already provided.


---------------------------------- Notes -------------------------------------

1. Work in progress, I plan to add new features of moon systems soon! 
2. Issues with collision and random direction change.
3. Make object with critical mass glow.

Ah! Almost forgot, if run from the console, you will see output if your planets collide with themselves. It would be nice to have some collision animation (no sound effects of course, unlike Hollywood have us believe).

