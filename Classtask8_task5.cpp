#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static pthread_key_t thread_key;

void *thread_func(void *arg) {
  int i, r;
  int id = *(int*) arg, stringsAmount;
  char* str = "Random number is";

  pthread_setspecific(thread_key, (void*) str);
  char* spec = (char*) pthread_getspecific(thread_key);
  stringsAmount = 1 + rand() % 10;

  for(i = 0; i < stringsAmount; i++) {
    r = 1 + rand() % 10;
    printf("I'm thread #%d. %s %d\n", id, spec, r);
  }
}

int main(int argc, char* argv[]) {
  srand(time(NULL));
  if(argc < 2) {
    fprintf(stderr,"Wrong number of arguments\n");
    return 1;
  }
  int n = atoi(argv[1]);
  pthread_t threads[n];
  int i;

  pthread_key_create(&thread_key, NULL);

  for(i = 0; i < n; i++) {
    if(pthread_create(&(threads[i]), NULL, &thread_func, &i) != 0) {
      fprintf(stderr,"Error\n");
      return 1;
    }
    sleep(1);
  }

  for(i = 0; i < n; i++) {
    if((pthread_join(threads[i], NULL) != 0)) {
      fprintf(stderr, "Join error\n");
      return 1;
    }
  }
  return 0;
}
