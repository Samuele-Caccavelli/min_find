SRCS = src/main.cpp src/Gradient.hpp src/Gradient.cpp src/Parameters.hpp src/Parameters.cpp
OBJS = main.o Parameters.o
EXEC = main
IJSON = ${PWD}/include/json/single_include/nlohmann/
IMUPARSERX = ${PWD}/include/muparserx/parser/

.PHONY = all clean

all: main

main: ${OBJS}
	g++ -std=c++20 main.o Parameters.o Gradient.o -o ${EXEC}

${OBJS} : ${SRCS}
	g++ -std=c++20 -c -I${IJSON} src/main.cpp src/Parameters.cpp src/Gradient.cpp

other : ./main.cpp
	g++ -std=c++20 -c -I${IMUPARSERX} ./main.cpp
	g++ -std=c++20 ./main.o -o ${EXEC}

clean:
	rm *.o
	rm ${EXEC}