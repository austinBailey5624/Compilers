assignment1: main.o State.o DFAState.o
	g++ -std=c++11 -g -Wall main.o State.o DFAState.o -o assignment1

main.o: main.cpp State.cpp State.h DFAState.h DFAState.cpp
	g++ -std=c++11 -g -c -Wall main.cpp State.cpp State.h DFAState.h DFAState.cpp

State.o: State.h State.cpp
	g++ -std=c++11 -g -c -Wall State.h State.cpp

DFAState.o: DFAState.h DFAState.cpp
	g++ -std=c++11 -g -c -Wall DFAState.h DFAState.cpp

clean:
	rm *.o assignment1
