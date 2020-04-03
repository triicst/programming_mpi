#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  /* code */
  MPI_Init(NULL, NULL);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  if (world_size != 2){
    fprintf(stderr, "Must use two process for this example\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  const int MAX_NUMBERS = 100;
  int numbers[MAX_NUMBERS];
  int number_amount;

  if (world_rank == 0){
    //Pick a random amount of interfers to send to process one
    srand(time(NULL));
    number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;

    // send the amount of interfers to process one
    MPI_Send(&numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD );
    printf("0 sent %d to 1\n", number_amount);
  } else if (world_rank == 1){
    MPI_status status;
    //Receive at most MAX_NUMBERS from process zero
    MPI_Recv(&numbers, number_amount, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    //After receiving the message, check the status to determine
    //how many numbers were actually recieved
    //Ham MPI_Get_count(MPI_status-structure, type_element, so_luong_variable)
    MPI_Get_count(&status, MPI_INT, &number_amount);
    printf("1 reveive %d numbers from 0, Messeage sour = %d, tag = %d\n", number_amount, status.MPI_SOURCE, status.MPI_TAG);

  }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}
