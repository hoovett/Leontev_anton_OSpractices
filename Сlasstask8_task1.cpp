#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int* checkArr;

void *det_thread_func(void *arg) {
  int n = *(int*)arg;
  while(1) {
    int flag = 0;
    for(int i = 0; i < n; i++) {
      if (checkArr[i] == 0) flag = 1;
    }
    if (flag = 0) break;
    for (int i = 0; i < n; i++) printf(":%d", checkArr[i]);
    printf("\n");
    sleep(1);
  }
}

void *join_thread_func(void *arg) {
  int num = *(int *)arg;
  sleep(num);
  int r = 1 + rand() % 10;
  printf("Random number %d\n", r);
  checkArr[num] = r;
  sleep(r);
  return NULL;
}

int main(int argc, char *argv[]){
  srand(time(NULL));

  if (argc < 2) {
    fprintf(stderr, "Too few arguments\n");
    return 1;
  }

  int n = atoi(argv[1]);
  checkArr = (int*)calloc(n, sizeof(int));

  pthread_attr_t attr;
  pthread_t detached_thread, joinable_thread;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  if(pthread_create(&detached_thread, &attr, &det_thread_func, &n) != 0) {
    fprintf(stderr, "Error\n");
    return 1;
  }

  for(int i = 0; i < n; i++) {
    if(pthread_create(&joinable_thread, NULL, &join_thread_func, &i) != 0) {
      fprintf(stderr, "Error\n");
      return 1;
    }
    sleep(1);
  }

  if((pthread_join(joinable_thread, NULL) != 0)) {
    fprintf(stderr, "Join error\n");
    return 1;
  }

  pthread_attr_destroy(&attr);
  return 0;
}
