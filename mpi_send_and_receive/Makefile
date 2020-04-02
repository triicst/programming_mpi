EXECS=mpi_send_and_receive
MPICC?=mpicc
all: ${EXECS}
mpi_send_and_receive: mpi_send_and_receive.c
	${MPICC} -o mpi_send_and_receive mpi_send_and_receive.c
clean:
	rm -f ${EXECS}
