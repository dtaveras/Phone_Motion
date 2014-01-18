# Makefile for Ardunio USB Simple Communication

all: client

client: main.o
	g++ main.o -o client

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o client