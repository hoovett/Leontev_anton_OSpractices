#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_func(void *arg) {
  int n = 100000;
  int m = 1;
  int i;
  int x = 1;
  double p = 0;
  if(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) != 0) {
    fprintf(stderr, "Setcanselstate error!\n");
  }
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
  for(i = 0; i < n; i++) {
    p += x * (1/(double)m);
    m += 2;
    x = -x;
    printf("Pi = %.5f\n", p*4);
    pthread_testcancel();
  }
  printf("Final Pi = %.2f\n", p*4);
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
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
  pthread_cancel(thread);

  if((pthread_join(thread, (void*)&status) != 0)) {
    fprintf(stderr,"Join error\n");
    return 1;
  }
  if (status == PTHREAD_CANCELED) printf("Thread canceled\n");
  pthread_attr_destroy(&attr);
  return 0;
}
