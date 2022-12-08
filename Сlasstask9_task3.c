#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

char line[100];


void sigalarm_handler(int signo) {
  if (signo == SIGALRM) {
    printf("%s\n", line);
    exit(EXIT_SUCCESS);
  }
}

int main(void) {
  char timer_str[10];
  printf("Enter time:");
  scanf("%s", &timer_str);
  int timer = atoi(&timer_str);
  printf("Enter line:");
  scanf("%s", &line);
  struct sigaction alrm_act = {
    sigalarm_handler,
    NULL,
    NULL,
    NULL,
    NULL
  };
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    if (sigaction(SIGALRM, &alrm_act, NULL) == SIG_ERR) {
      fprintf(stderr, "Error.\n");
      exit(-1);
    }
    alarm(timer);
    pause();
  }
  else {
    exit(0);
  }

  return EXIT_SUCCESS;
}
