CXX      ?= g++
CXXFLAGS ?= -std=c++20
SRCS = src/main.cpp src/Parameters.cpp src/Gradient.cpp 
HEADERS = src/Parameters.hpp src/Gradient.hpp
OBJS = main.o Parameters.o Gradient.o
EXEC = main
IJSON = ${PWD}/include/json/single_include/nlohmann/
IMUPARSERX = ${PWD}/include/muparserx/parser/

.PHONY = all clean

all: ${EXEC}

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${EXEC}

${OBJS} : ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} -c -I${IJSON} ${SRCS}

other : ./main.cpp
	g++ -std=c++20 -c -I${IMUPARSERX} ./main.cpp
	g++ -std=c++20 ./main.o -o ${EXEC}

clean:
	${RM} *.o

distclean: clean
	$(RM) $(EXEC)