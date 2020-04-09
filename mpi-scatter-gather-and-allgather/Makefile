EXECS=avg 
MPICC?=mpicc

all:	${EXECS}

avg:	avg.c
	${MPICC} -o avg avg.c

clean:
		rm -rf ${EXECS}
