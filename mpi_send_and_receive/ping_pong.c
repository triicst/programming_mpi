#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  /* code */
  const int PING_PONG_LIMIT = 10;

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int ping_pong_count = 0;

  int parnet_rank = (world_rank + 1) % 2;

  while (ping_pong_count < PING_PONG_LIMIT) {
    /* code */
    if (world_rank == ping_pong_count % 2){
      // Tang ping_pong truoc khi send
      ping_pong_count++;
      MPI_Send(&ping_pong_count, 1, MPI_INT, parnet_rank, 0, MPI_COMM_WORLD);
      printf("%d sent and incremented ping_pong_count"
              "%d to %d\n",world_rank, ping_pong_count, parnet_rank);
    } else{
      MPI_Recv(&ping_pong_count, 1, MPI_INT, world_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%d receive ping_pong_count %d from %d\n",world_rank, ping_pong_count, parnet_rank);
    }
  }

  MPI_Finalize();
  return 0;
}
