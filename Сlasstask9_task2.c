#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler1(int signo) {
  if (signo == SIGUSR1) {
    printf("Parent[PID = %d] received signal: %s\n",getpid(),sys_siglist[signo]);
  }
  else {
    fprintf(stderr, "Smth goes wrong\n");
    exit(-1);
  }
}

void signal_handler2(int signo) {

  if (signo == SIGUSR1) {
    printf("Child[PID = %d] received signal: %s\n", getpid(), sys_siglist[signo]);
  }
  else {
    fprintf(stderr, "Smth goes wrong\n");
    exit(-1);
  }
}

int main(void) {
  pid_t childp;
  pid_t mainp = getpid();
  if (signal(SIGUSR1, signal_handler1) == SIG_ERR) {
    fprintf(stderr, "Can't process SIGUSR1\n");
    exit(-1);
  }
  childp = fork();
  if(childp == 0){
    if (signal(SIGUSR1, signal_handler2) == SIG_ERR) {
      fprintf(stderr, "Can't process SIGUSR1\n");
      exit(-1);
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
