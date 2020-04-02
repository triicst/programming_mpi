EXECS=helloworld
MPICC?=mpicc
all: ${EXECS}
	${MPICC} -o helloworld helloworld.c
clean:
	rm ${EXECS}
