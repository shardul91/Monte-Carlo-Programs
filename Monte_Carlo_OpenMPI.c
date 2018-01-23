#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

long long int total_number_of_tosses, tosses_per_thread;//Total number of tosses
long long int number_in_circle = 0; //Each thread is adding its result to this variable.
int thread_count; //Number of threads.

//returns a random number in the range -1 to 1.
double rand_double() {
  return 2 * (rand() / (double)RAND_MAX) - 1;
}

int main()
{
  double pi_estimate;//At the end the function main stores the output into this variable and print it.

  printf("Enter number of threads and the total number of tosses: ");
  scanf("%d%lld", &thread_count, &total_number_of_tosses);
  srand((long)time(NULL));

  //Using the following loop to make it divisible by thread_count.
  while (total_number_of_tosses % thread_count != 0) {
       total_number_of_tosses++;
  }
  //Complete the rest of this function.
  tosses_per_thread = total_number_of_tosses/thread_count;

   #pragma omp parallel num_threads(thread_count)
   {
    double x, y, distance_squared;
    int toss,number_in_circle_in_thread=0;
   for (toss = 0; toss < tosses_per_thread; toss++){
     x = rand_double();
     y = rand_double();
     distance_squared = x*x + y*y;
    if (distance_squared <= 1)
      number_in_circle_in_thread++;
   }

  #pragma omp critical
    number_in_circle += number_in_circle_in_thread;

  }

   pi_estimate = 4 * number_in_circle / ((double)total_number_of_tosses);
   printf("Estimated pi = %f\n", pi_estimate);

  return 0;
}
