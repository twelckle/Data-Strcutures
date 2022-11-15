output: main.o mymath.o
	g++ main.o mymath.o -o output
mymath.o: mymath.cpp mymath.h 
	g++ -c mymath.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o output