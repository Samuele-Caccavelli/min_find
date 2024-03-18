.PHONY = all

all : main

main : main.o
	g++ -std=c++20 main.o -o main

main.o : main.cpp Gradient.hpp Parameters.hpp
	g++ -std=c++20 -c main.cpp