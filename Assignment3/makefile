output: main.o contactbst.o myvector.o contact.o
	g++ main.o contactbst.o myvector.o contact.o -o output

main.o: main.cpp
	g++ -c main.cpp contactbst.cpp myvector.cpp contact.cpp

contactbst.o: contactbst.cpp contactbst.h
	g++ -c contactbst.cpp myvector.cpp contact.cpp 

myvector.o: myvector.cpp myvector.h
	g++ -c myvector.cpp contact.cpp

contact.o: contact.cpp contact.h
	g++ -c contact.cpp

clean:
	rm *.o output