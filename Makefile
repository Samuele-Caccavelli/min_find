SRCS = main.cpp Gradient.hpp Gradient.cpp Parameters.hpp Parameters.cpp
OBJS = main.o Parameters.o
EXEC = main

.PHONY = all clean

all: main

main: ${OBJS}
	g++ -std=c++20 main.o Parameters.o Gradient.o -o ${EXEC}

${OBJS} : ${SRCS}
	g++ -std=c++20 -c main.cpp Parameters.cpp Gradient.cpp

clean:
	rm *.o
	rm ${EXEC}