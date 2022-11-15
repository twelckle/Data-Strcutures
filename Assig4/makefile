output: main.o flighthashtable.o mylist.o flightticket.o
	g++ main.o flighthashtable.cpp mylist.cpp flightticket.cpp -o output

main.o: main.cpp
	g++ -c main.cpp flighthashtable.cpp mylist.cpp flightticket.cpp

flighthashtable.o: flighthashtable.cpp flighthashtable.h
	g++ -c flightticket.cpp mylist.cpp

mylist.o: mylist.cpp mylist.h
	g++ -c mylist.cpp flighthashtable.cpp

flightticket.o: flightticket.cpp flightticket.h
	g++ -c flightticket.cpp

clean:
	rm *.o output