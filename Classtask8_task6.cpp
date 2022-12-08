#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cleanHandler() {
  fprintf(stderr, "Clean handler started work.\n");
}

void *thread_func() {
  int i = 0;
  if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) != 0) {
    printf("Setcanselstate error!\n");
  }
  if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL) != 0) {
    printf("Setcanseltype error!\n");
  }
  while(1) {
    printf("Iteration %d\n", i++);
    sleep(1);
  }
}

int main(int argc, char* argv[]) {
  if(argc < 2) {
    printf("Wrong number of arguments\n");
    return 1;
  }

  pthread_t thread;
  void* status;

  if(pthread_create(&thread, NULL, &thread_func, NULL) != 0) {
    fprintf(stderr, "Error\n");
    return 1;
  }

  int n = atoi(argv[1]);
  sleep(n);

  pthread_cleanup_push(cleanHandler, NULL);
  pthread_cleanup_pop(1);

  if(pthread_cancel(thread) != 0) {
    printf("Cancel error!\n");
  }

  if((pthread_join(thread, (void*)&status) != 0)) {
    fprintf(stderr,"Join error\n");
    return 1;
  }
  if(status == PTHREAD_CANCELED) fprintf(stderr, "Main thread finished work\n");
  return 0;
}
