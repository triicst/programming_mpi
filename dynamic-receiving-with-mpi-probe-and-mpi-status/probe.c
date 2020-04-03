#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
  /* code */
  MPI_Init(NULL,NULL);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  if (world_size != 2){
    fprintf(stderr, "Must use tow  process%s\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int number_amount;
  if (world_rank == 0){
    const int MAX_NUMBERS = 100;
    int numbers[MAX_NUMBERS];
    //Pick a random amount of integers to send to process one
    srand(time(NULL));
    number_amount = (rand() / (float)RAND_MAX)* MAX_NUMBERS;
    //Send the random amount of integers to process one
    MPI_Send(&numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
    printf("0 sent %d numbers to 1%s\n", number_amount);
  } else if (world_rank == 1){
    MPI_Status status;
    //MPI_Proce do thong tin imcomming message from procee zero
    // MPI_Probe(
    //     int source,
    //     int tag,
    //     MPI_Comm comm,
    //     MPI_Status* status)
    MPI_Probe(0,0, MPI_COMM_WORLD, &status);
    //When probe returns, the status object has the size and other attributes of the imcomming message, Get the message size
    MPI_Get_count(&status, MPI_INT, &number_amount);

    //Allocate a buffer to hold the imcomming number
    int* number_buf = (int*)malloc(sizeof(int) * number_amount);

    //Now recevice the message with the allocate buffer
    MPI_Recv(number_buf, number_amount, MPI_INT, 0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("1 dynamic recevice %d numbers from 0, \n", number_amount);
    free(number_buf);
  }

  MPI_Finalize();
  return 0;
}
