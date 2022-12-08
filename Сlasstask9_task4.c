#include <stdio.h>
#include <stdio_ext.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/wait.h>
#include <errno.h>

void child_sig_handler1(int signo, siginfo_t *sig, void *ucontext) {
  if (signo == SIGUSR1) {
    void *ptr = sig->si_value.sival_ptr;
    int c = sig->si_value.sival_int;
    printf("SIGNO = %d\tSTRING REPRESANTATION = %s\tCOUNT = %d\n", signo, sys_siglist[signo], c);
  }
}

void child_sig_handler2(int signo) {
  if (signo == SIGTERM) {
    printf("SIGTERM catched: exiting...\n");
    exit(0);
  }
}

int main(void) {
  int count = 1;
  pid_t childp = fork();
  if (childp == 0) {
    struct sigaction child_act;
    child_act.sa_flags = SA_SIGINFO;
    child_act.sa_sigaction = &child_sig_handler1;

    if (sigaction(SIGUSR1, &child_act, NULL)) {
      fprintf(stderr, "Error occured.SIGUSR1\n");
      exit(-1);
    }

    if (signal(SIGTERM, child_sig_handler2) == SIG_ERR) {
      fprintf(stderr, "Error occured.SIGTERM\n");
      exit(-1);
    }

    while(1){
      pause();
    }
  }
  else {
    sigval_t value;
    while (count != 11) {
      
      value.sival_int = count;
      printf(" ");
      int status = sigqueue(childp, SIGUSR1, value);
      if (status) {
        fprintf(stderr, "Error occured.MAINP %d\n", errno);
        exit(-1);
      }
      count++;
      sleep(1);
    }
    kill(childp, SIGTERM);
    pid_t childpw = wait(&childp);
    exit(0);
  }
}
