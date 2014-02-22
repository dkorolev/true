CFLAGS=-O3
CPP=g++ ${CFLAGS}
CPP11=${CPP} -std=c++11

BINARY=bool

all: ${BINARY}

${BINARY}: bool.cc
	${CPP11} -o $@ $<

clean:
	rm -rf ${BINARY}
