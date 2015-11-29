all: planets

planets.o: Celes.cpp
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -o planets.o "./Celes.cpp"

planets: planets.o	
	g++ -o planets planets.o -lGLU -lGL -lglut

clean:
	rm -rf planets.o planets
