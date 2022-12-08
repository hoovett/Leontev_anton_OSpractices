#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

char *line;

void sigalarm_handler(int signo) {
  if (signo == SIGALRM) {
    printf("%s\n", line);
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char *argv[]) {
  if(argc < 3) {
    fprintf(stderr,"Wrong number of arguments\n");
    exit(EXIT_FAILURE);
  }
  int timer = atoi(argv[1]);
  line = argv[2];
  struct sigaction alrm_act = {
    sigalarm_handler, NULL, NULL, NULL, NULL
  };
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    if (sigaction(SIGALRM, &alrm_act, NULL) == SIG_ERR) {
      fprintf(stderr, "Error\n");
      exit(EXIT_FAILURE);
    }
    alarm(timer);
    pause();
  }
  else {
    exit(EXIT_SUCCESS);
  }

  return EXIT_SUCCESS;
}
