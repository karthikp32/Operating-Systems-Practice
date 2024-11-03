#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>


#define SLEEP_SEC 3
#define NUM_MULS 100000000
#define NUM_MALLOCS 100000
#define MALLOC_SIZE 1000

// TODO define this struct
struct profile_times {
  struct timeval curr_time;
  double curr_user_time_secs;
  double curr_kernel_time_secs;
  double curr_user_time_usecs;
  double curr_kernel_time_usecs;
};

// TODO populate the given struct with starting information
void profile_start(struct profile_times *t) {

  if (gettimeofday(&t->curr_time, NULL) != 0) {
        perror("gettimeofday failed");
  }

  struct rusage usage;

  if (getrusage(RUSAGE_SELF, &usage) == 0) {
      t->curr_user_time_secs = usage.ru_utime.tv_sec;
      t->curr_kernel_time_secs = usage.ru_stime.tv_sec;
      t->curr_user_time_usecs = usage.ru_utime.tv_usec;
      t->curr_kernel_time_usecs = usage.ru_stime.tv_usec;
  }


}

// TODO given starting information, compute and log differences to now
void profile_log(struct profile_times *t, int function_id) {
  struct timeval current_time;
  if (gettimeofday(&current_time, NULL) != 0) {
        perror("gettimeofday failed");
  }

  double elapsed_real_time_secs = current_time.tv_sec - t->curr_time.tv_sec;
  double elapsed_real_time_micro = current_time.tv_usec - t->curr_time.tv_usec;
  double elapsed_real_time = elapsed_real_time_secs + elapsed_real_time_micro * 1e-6;

  struct rusage usage;

  if (getrusage(RUSAGE_SELF, &usage) == 0) {
      double curr_user_time_secs = usage.ru_utime.tv_sec;
      double curr_kernel_time_secs = usage.ru_stime.tv_sec;
      double curr_user_time_micro = usage.ru_utime.tv_usec;
      double curr_sys_time_micro = usage.ru_stime.tv_usec;

      double elasped_user_time_secs = curr_user_time_secs - t->curr_user_time_secs;
      double elasped_kernel_time_secs = curr_kernel_time_secs - t->curr_kernel_time_secs;
      double elasped_user_time_micro = curr_user_time_micro - t->curr_user_time_usecs;
      double elasped_kernel_time_micro = curr_sys_time_micro - t->curr_kernel_time_usecs;

      double total_elapsed_user_time = elasped_user_time_secs + elasped_user_time_micro * 1e-6; 
      double total_elapsed_kernel_time = elasped_kernel_time_secs + elasped_kernel_time_micro * 1e-6; 

      printf("Real time elapsed: %.6f seconds for function %d\n", elapsed_real_time, function_id);
      printf("User CPU time elapsed: %.6f seconds for function %d\n", total_elapsed_user_time, function_id);
      printf("System CPU time: %.6f seconds for function %d\n\n", total_elapsed_kernel_time,  function_id);
  }
}

int main(int argc, char *argv[]) {
  struct profile_times t;

  // TODO profile doing a bunch of floating point muls
  float x = 1.0;
  profile_start(&t);
  for (int i = 0; i < NUM_MULS; i++)
    x *= 1.1;
  profile_log(&t, 1);

  // TODO profile doing a bunch of mallocs
  profile_start(&t);
  void *p;
  for (int i = 0; i < NUM_MALLOCS; i++)
    p = malloc(MALLOC_SIZE);
  profile_log(&t, 2);

  // TODO profile sleeping
  profile_start(&t);
  sleep(SLEEP_SEC);
  profile_log(&t, 3);
}
