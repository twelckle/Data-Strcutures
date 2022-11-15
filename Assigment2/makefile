output: main.o admin.o fitness.o member.o linkedlist1.o linkedstack.o
	g++ assignment1.o admin.o fitness.o member.o linkedlist1.o linkedstack.o -o output

main.o: main.cpp
	g++ -c main.cpp admin.cpp fitness.cpp member.cpp linkedlist1.cpp linkedstack.cpp

linkedlist1.o: linkedlist1.cpp linkedlist1.h
	g++ -c: linkedlist1.cpp admin.cpp member.cpp fitness.cpp linkedstack.cpp

linkedstack.o: linkedstack.cpp linkedstack.h
	g++ -c: linkedstack.cpp linkedlist1.cpp fitness.cpp

fitness.o: fitness.cpp fitness.h
	g++ -c fitness.cpp linkedstack.cpp

admin.o: admin.cpp admin.h
	g++ -c admin.cpp

member.o: member.cpp member.h
	g++ -c member.cpp

clean:
	rm *.o output