dh: main.o
	g++ main.o -o dh 
main.o: main.cpp
	g++ -c main.cpp
