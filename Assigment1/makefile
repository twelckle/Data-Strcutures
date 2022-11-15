output: assignment1.o admin.o fitness.o member.o
	g++ assignment1.o admin.o member.o fitness.o -o output

assigment1.o: assignment1.cpp assignment1.h
	g++ -c assignment1.cpp admin.cpp fitness.cpp member.cpp

admin.o: admin.cpp admin.h
	g++ -c admin.cpp fitness.cpp member.cpp

member.o: member.cpp member.h
	g++ -c member.cpp fitness.cpp

fitness.o: fitness.cpp fitness.h
	g++ -c fitness.cpp

clean:
	rm *.o output