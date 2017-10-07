assignment1: main.o State.o
	g++ -std=c++11 -g -Wall main.o State.o -o assignment1

main.o: main.cpp State.cpp State.h
	g++ -std=c++11 -g -c -Wall main.cpp State.cpp State.h

State.o: State.h State.cpp
	g++ -std=c++11 -g -c -Wall State.h State.cpp

clean:
	rm *.o assignment1
