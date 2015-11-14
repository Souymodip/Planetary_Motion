# Planetary_Motion

---------------------------------- Description -------------------------------

1. A view of our solar system, as defined by Newtonian Mechanics.
2. The program is writen in openGL(C++ / linux).
3. The program is ment for teaching children on how celestial objects behave in space.
4 .Changing the program code is very simple, and comlex model of planetary system can be build, by varing number of planets,mass of each planet, even the gravitational constant can be tinkered with for observing its affect on the mechanics.

----------------------------------- compiling --------------------------------

1. The code is tested for linux operating system.
2. Libraries freeglut.h and gl.h are necessary and should be stored in a folder include\GL.
3. Run the following command
4. - g++ -O0 -g3 -Wall -c -fmessage-length=0 -o planets.o "./fist.cpp" 
   - g++ -o planets planets.o -lGLU -lGL -lglut
5. Double click planets (or type - ./planet)


---------------------------------- Editing ----------------------------------- 

1. The files fist.cpp and basic_shape.h contains core of the implemtation.
2. For start, just open the file "initializer.h". Follow the simple instruction to create your own planet systes and compile and run.
3. A running example is already provided


---------------------------------- Notes -------------------------------------

1. Work in progress, I plane to add new features of moon systems soon! 
 

