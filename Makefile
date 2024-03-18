SRCS = main.cpp Gradient.hpp Parameters.hpp Parameters.cpp
OBJS = main.o Parameters.o
EXEC = main

.PHONY = all clean

all: main

main: ${OBJS}
	g++ -std=c++20 main.o Parameters.o -o ${EXEC}

${OBJS} : ${SRCS}
	g++ -std=c++20 -c main.cpp Parameters.cpp

clean:
	rm ${EXEC}
	rm *.o