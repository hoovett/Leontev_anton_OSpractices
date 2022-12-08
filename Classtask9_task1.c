#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo)
{
  if (signo == SIGINT) {
    printf("SIGINT catched\n");
  }
  else 
    if(signo == SIGTERM) {
      printf("SIGTERM catched\n");
  }
  else {
    fprintf(stderr, "Uknown signal\n");
    exit(-1);
  }
  exit(0);
}

// int main(void) {
//   if (signal(SIGINT, signal_handler) == SIG_ERR) {
//     fprintf(stderr, "Can't process SIGINT\n");
//     exit(-1);
//   }
//   if (signal(SIGTERM, signal_handler) == SIG_ERR) {
//     fprintf(stderr, "Can't process SIGTERM\n");
//     exit(-1);
//   }
//   if (signal(SIGPROF, SIG_DFL) == SIG_ERR) {
//     fprintf(stderr, "Can't reset SIGPROF\n");
//     exit(-1);
//   }
//   if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
//     fprintf(stderr, "Can't ignore SIGHUP\n");
//     exit(1-);
//   }
//
//   while(1) {
//     pause();
//   }
// }

int main(void) {

  struct sigaction sigint_act = {
    signal_handler, 
    NULL,
    NULL,
    NULL,
    NULL,
  };
  if (sigaction(SIGINT, &sigint_act, NULL) == SIG_ERR) {
    fprintf(stderr, "Can't process SIGINT!\n");
    exit(-1);
  }

  struct sigaction sigterm_act = {
    signal_handler,
    NULL,
    NULL,
    NULL,
    NULL,
  };

  if (sigaction(SIGTERM, &sigterm_act, NULL) == SIG_ERR) {
    fprintf(stderr, "Can't process SIGTERM!\n");
    exit(-1);
  }

  struct sigaction sigprof_act = {
    SIG_DFL,
    NULL,
    NULL,
    NULL,
    NULL,
  };

  if (sigaction(SIGPROF, &sigprof_act, NULL) == SIG_ERR) {
    fprintf(stderr, "Can't restore SIGPROF!\n");
    exit(-1);
  }

  struct sigaction sighup_act = {
    SIG_IGN,
    NULL,
    NULL,
    NULL,
    NULL,
  };

  if (sigaction(SIGHUP, &sighup_act, NULL) == SIG_ERR) {
    fprintf(stderr, "Can't ignore SIGHUP!\n");
    exit(-1);
  }

  while(1) {
    pause();
  }
}
