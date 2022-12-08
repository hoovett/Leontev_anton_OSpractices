#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void signal_handler1(int signo) {
  if (signo == SIGUSR1) {
    printf("Parent[PID = %d] received signal: %s\n", getpid(), strsignal(signo));
  }
  else {
    fprintf(stderr, "Error\n");
    exit(EXIT_FAILURE);
  }
}

void signal_handler2(int signo) {

  if (signo == SIGUSR1) {
    printf("Child[PID = %d] received signal: %s\n", getpid(), strsignal(signo));
  }
  else {
    fprintf(stderr, "Error\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  pid_t childp;
  pid_t mainp = getpid();
  if (signal(SIGUSR1, signal_handler1) == SIG_ERR) {
    fprintf(stderr, "Can't process SIGUSR1\n");
    exit(EXIT_FAILURE);
  }
  childp = fork();
  if(childp == 0){
    if (signal(SIGUSR1, signal_handler2) == SIG_ERR) {
      fprintf(stderr, "Can't process SIGUSR1\n");
      exit(EXIT_FAILURE);
    }
  }
  while(1) {
    if (childp == 0) {
      pause();
      kill(mainp, SIGUSR1);
      sleep(3);
    }
    else {
      sleep(3);
      kill(childp, SIGUSR1);
      pause();
    }
  }
}
