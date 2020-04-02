EXECS=mpi_send_and_receive ping_pong
MPICC?=mpicc

all: ${EXECS}

mpi_send_and_receive: mpi_send_and_receive.c
	${MPICC} -o mpi_send_and_receive mpi_send_and_receive.c

ping_pong: ping_pong.c
	${MPICC} -o ping_pong ping_pong.c

clean:
	rm -f ${EXECS}
