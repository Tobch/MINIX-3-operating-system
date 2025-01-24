/*
	I created my own longrun without the 'iteration and value' printf -- so as to avoid preemption during priority scheduler which gets 
	preempted during the above mentioned printf; it being an IO operation.
*/

//for CPU bound processes 


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
//#include "schedproc.h"
#include <sys/resource.h>


#define LOOP_COUNT_MIN 100
#define LOOP_COUNT_MAX 100000000

long long subtime(struct timeval start,struct timeval end)
{
  return 1000000*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec);
}

int main (int argc, char *argv[])
{
  char *idStr;
  unsigned int	v;
  int	i = 0;
  int	iteration = 1;
  int	loopCount;
  int	maxloops;



  if (argc < 3 ) 
  {
    printf ("Usage: %s <id> <loop count> [max loops]\n", argv[0]);
    exit (-1);
  }

  v = getpid ();

  idStr = argv[1];
  loopCount = atoi (argv[2]);
  if ((loopCount < LOOP_COUNT_MIN) || (loopCount > LOOP_COUNT_MAX)) 
  {
    printf ("%s: loop count must be between %d and %d (passed %s)\n", argv[0], LOOP_COUNT_MIN, LOOP_COUNT_MAX, argv[2]);
    exit (-1);
  }

  if (argc == 4) 
  {
    maxloops = atoi (argv[3]);
  } 
  else 
  {
    maxloops = 0;
  }


  struct timeval start,end,wait,curr; //store start, end (turnaround time) and temporary times for calculations
  double waiting_time=0; 

  double square_root = 0;
  //double number = strtod(argv[4], NULL);
  gettimeofday(&start,NULL);
      
  while (1) 
  {
    for (int i = 0; i < loopCount; i++) {
      v = (v << 4) - v;
      
      

}
      if (iteration == maxloops) 
      {
		 break;
      }

      gettimeofday(&wait,NULL);
      fflush(stdout); //basically the waiting time of the preemption due to fflush
      gettimeofday(&curr,NULL);
      waiting_time=waiting_time+subtime(wait,curr);// add to waiting time
      iteration += 1;
  }

  int priority = getpriority(PRIO_PROCESS, getpid());

square_root = sqrt(25); // Calculate square root

  gettimeofday(&end,NULL);
  printf ("\n\nThe CPU bound final value of v is 0x%08x\n", v);
  printf("Process Id: %d\n",abs(v));
  printf("Priority: %d\n",priority);
  printf("CPU Bound: Square root of %f is %f\n", 25.0, square_root);
  printf("Turnaround time = %0.6lf s\n",(double)subtime(start,end)/1000000);
  printf("Waiting time = %0.6lf s\n",waiting_time/1000000);
  printf("Burst time = %0.6lf s\n",(double)subtime(start,end)/1000000-waiting_time/1000000);
}
