#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_func(void *arg) {
  int n = *(int*)arg;
  if(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL) != 0) {
    printf("Setcanselstate error!\n");
  }
  for(int i = 0; i < n*2; i++) {
    printf("Iteration %d\n", i);
    sleep(1);
  }
}

int main(int argc, char* argv[]) {
  if(argc < 2) {
    fprintf(stderr,"Wrong number of arguments\n");
    return 1;
  }
  pthread_attr_t attr;
  pthread_t thread;
  int *status;
  int n = atoi(argv[1]);

  pthread_attr_init(&attr);
  if(pthread_create(&thread, &attr, &thread_func, &n) != 0) {
    fprintf(stderr,"Error\n");
    return 1;
  }

  sleep(n);

  if(pthread_cancel(thread) != 0) {
    printf("Cancel error!\n");
  }

  if((pthread_join(thread, (void*)&status) != 0)) {
    fprintf(stderr,"Join error\n");
    return 1;
  }

  if(status == PTHREAD_CANCELED) printf("Thread canceled\n");
  else printf("Thread finished by itself\n");
  pthread_attr_destroy(&attr);
  return 0;
}
