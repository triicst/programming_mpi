EXECS=my_bcast
MPICC?=mpicc

all: ${EXECS}

my_bcast: my_bcast.c
	${MPICC} -o my_bcast my_bcast.c

clean:
	rm -rf ${EXECS}
