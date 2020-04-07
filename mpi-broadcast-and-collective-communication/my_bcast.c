#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void my_bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator){
  int work_rank;
  MPI_Comm_rank(communicator, &work_rank);

  int work_size;
  MPI_Comm_size(communicator, &work_size);
  if (work_rank == root){
    //If we are the root procees, send our data to everyone
    int i;
    for (i = 0; i < work_size, i++){
      if (i != work_rank){
        MPI_Send(data, count, datatype, i, 0, communicator );
      }
    }
  } else {
    MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
  }
}
int main(int argc, char** argv) {
  /* code */
  MPI_Init(NULL,NULL);

  int work_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &work_rank);

  int work_size;
  MPI_Comm_size(MPI_COMM_WORLD, &work_size);
  int data;
  if (work_rank == 0){
    data = 100;
    printf("Process 0 broadcasting data %d\n",data);
    my_bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
  }  else{
    my_bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d received data %d from root process\n", work_rank, data);
  }
  return 0;
}
