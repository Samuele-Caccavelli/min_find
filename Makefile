SRCS = src/main.cpp src/Gradient.hpp src/Gradient.cpp src/Parameters.hpp src/Parameters.cpp
OBJS = main.o Parameters.o
EXEC = main

.PHONY = all clean

all: main

main: ${OBJS}
	g++ -std=c++20 main.o Parameters.o Gradient.o -o ${EXEC}

${OBJS} : ${SRCS}
	g++ -std=c++20 -c -I${PWD}/include  src/main.cpp src/Parameters.cpp src/Gradient.cpp

clean:
	rm *.o
	rm ${EXEC}