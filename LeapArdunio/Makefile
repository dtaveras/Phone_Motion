# Makefile for Ardunio USB Simple Communication

all: ardunio

ardunio: main.o
	g++ main.o -o ardunio

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o ardunio