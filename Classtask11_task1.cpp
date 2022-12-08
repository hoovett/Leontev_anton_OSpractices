#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo)
{
  if(signo == SIGINT) {
    printf("SIGINT catched\n");
  }
  else if(signo == SIGTERM) {
	printf("SIGTERM catched\n");
  }
  else{
    fprintf(stderr, "Uknown signal\n");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

int main(void) {

  struct sigaction sigint_act = {
    signal_handler, NULL, NULL, NULL, NULL,
  };
  if (sigaction(SIGINT, &sigint_act, NULL) == SIG_ERR) {
    fprintf(stderr, "Can't process SIGINT!\n");
    exit(EXIT_FAILURE);
  }

  struct sigaction sigterm_act = {
    signal_handler, NULL, NULL, NULL, NULL,
  };

  if (sigaction(SIGTERM, &sigterm_act, NULL) == SIG_ERR) {
    fprintf(stderr, "Can't process SIGTERM!\n");
    exit(EXIT_FAILURE);
  }

  struct sigaction sigprof_act = {
    SIG_DFL, NULL, NULL, NULL, NULL,
  };

  if (sigaction(SIGPROF, &sigprof_act, NULL) == SIG_ERR) {
    fprintf(stderr, "Can't restore SIGPROF!\n");
    exit(EXIT_FAILURE);
  }

  struct sigaction sighup_act = {
    SIG_IGN, NULL, NULL, NULL, NULL,
  };

  if (sigaction(SIGHUP, &sighup_act, NULL) == SIG_ERR) {
    fprintf(stderr, "Can't ignore SIGHUP!\n");
    exit(EXIT_FAILURE);
  }

  while(1) {
    pause();
  }
}
