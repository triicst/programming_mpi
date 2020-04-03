EXECS=check_status
MPICC?=mpicc

all: ${EXECS}

check_status: check_status.c
	${MPICC} -o check_status check_status.c

clean:
	rm -f ${EXECS}
