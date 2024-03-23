CXX      ?= g++
CXXFLAGS ?= -std=c++20
SRCS = src/main.cpp src/Parameters.cpp src/Gradient.cpp 
HEADERS = src/Parameters.hpp src/Gradient.hpp src/Mup_wrapper.hpp
OBJS = main.o Parameters.o Gradient.o
EXEC = main
IJSON = ${PWD}/include
IMUPARSERX = ${PWD}/include/muparserx
LMUPARSERX = ${PWD}/lib
MUPARSERXNAME = libmuparserx.a

.PHONY = all clean

all: ${EXEC}

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${EXEC} -L${LMUPARSERX} -l:${MUPARSERXNAME}

${OBJS} : ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} -c -I${IJSON} -I${IMUPARSERX} ${SRCS}

clean:
	${RM} *.o

distclean: clean
	$(RM) $(EXEC)