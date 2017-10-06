assignment1: main.o State.o FileReader.o
	g++ -std=c++11 -g -Wall main.o State.o -o assignment1

main.o: main.cpp State.cpp State.h FileReader.h FileReader.cpp
	g++ -std=c++11 -g -c -Wall main.cpp State.cpp State.h FileReader.h FileReader.cpp

State.o: State.h State.cpp
	g++ -std=c++11 -g -c -Wall State.h State.cpp

FileReader.o: FileReader.h FileReader.cpp
	g++ -std=c++11 -g -c -Wall FileReader.h FileReader.cpp

clean:
	rm *.o assignment1
