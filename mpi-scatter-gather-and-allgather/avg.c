#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

float *create_rand_nums(int num_elements){
  float *rand_nums = (float *)malloc(sizeof(float) * num_elements);
  //assert function dung de chuan doan loi, void assert(int bieu-thuc),
  //bieu thuc co the la bien hoc la bieu thuc, neu tra ve TRUE thi khong lam gi
  // neu tra ve FALSE thi hien thi thong bao loi treen stderr va ngung thuc thi chuong trinh
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++){
    rand_nums[i] = (rand() / (float)RAND_MAX);
  }
  return rand_nums;
}
float compute_avg(float *array, int num_elements){
  float sum = 0.f;
  int i;
  for (i = 0;i < num_elements; i++){
    sum += array[i];
  }
  return sum / num_elements;
}
int main(int argc, char **argv) {
  /* code */
  if (argc != 2){
    fprintf(stderr, "Usage: avg num_elements_per_proc\n");
    exit(1);
  }
    //convert from string to integer with use atoi function in c
  int num_elements_per_proc = atoi(argv[1])
  // Seed the random number generator to get different results each time
  srand(time(NULL));

  MPI_Init(NULL,NULL);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLRD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLRD, &world_rank);
  //Create a random array of elements on the root process . Its total
  //size will be the number of elements per process time the number
  // of process
  float *rand_nums = NULL;
  if (world_rank == 0){
    rand_nums = create_rand_nums(num_elements_per_proc * world_size);
  }
  //For each process, create a buffer that will hold a subnet of the entrire
  // array
  float *sub_rand_nums = (float *)malloc(sizeof(float) * num_elements_per_proc);
  assert(sub_rand_nums != NULL);

  //Scatter the random numbers from the root process to all process in
  // the MPI world
  //MPI_Scatter(
  //void *send_data,
  //int send_cout,
  //MPI_Datatype send_datatype,
  //void *recv_data, --->buffer per processor
  //int recv_count
  //MPI_Datatype recv_datatype,
  //int root,
  //MPI_Comm  communicator)
  MPI_Scatter(rand_nums, num_elements_per_proc, MPI_FLOAT, sub_rand_nums, num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WOLRD);
  //Compute the average of your subset
  float sub_avg = compute_avg(sub_rand_nums, num_elements_per_proc);
  //Gather all partical averages down to the root process
  float *sub_avgs = NULL;
  if (world_rank == 0){
    sub_avgs = (float *)malloc(sizeof(float) * world_size);
    assert(sub_avgs != NULL);
  }
  // MPI_Gather(
  //   void* send_data,
  //   int send_count,
  //   MPI_Datatype send_datatype,
  //   void* recv_data,
  //   int recv_count,
  //   MPI_Datatype recv_datatype,
  //   int root,
  //   MPI_Comm communicator)
  MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLRD);
  // Now that we have all of the partial averages on the root, compute the
// total average of all numbers. Since we are assuming each process computed
// an average across an equal amount of elements, this computation will
// produce the correct answer.
  if (world_rank == 0){
    float avg = compute_avg(sub_avgs, world_size);
    printf("Avg of all elements is %f\n", avg);
    //Compute the average across the original data for comparison
    float original_data_avg = compute_avg(rand_nums, num_elements_per_proc * world_size);
    printf("Avg computed accross original data is %f\n", original_data_avg);
  }
  if (world_rank == 0){
    free(rand_nums);
    free(sub_avgs);
  }
  free(sub_rand_nums);
  MPI_Barrier(MPI_COMM_WORLRD);
  MPI_Finalize();
  return 0;
}
