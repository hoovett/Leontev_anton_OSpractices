#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void cleanHandler(){
	// look at me. i'm handler. i'm useless.
	fprintf(stderr, "Clean handler started its work.\n");
}

void *thread_func(){	
	int i = 0;
	// print some useless stuff to stdout every second 10 times
	while(1){
		printf("Iteration %d\n", i++);
		sleep(1);
		if (i == 10)
			break;			
	}
	// print some useless message to stderr
	fprintf(stderr, "Thread finished its work\n");
}
	
int main(int argc, char* argv[]){	
	if (argc != 2) {
		printf("Wrong number of arguments\n");
		exit(0);
	}	
		i == 10)
	pthread_t thread;
	void* res;		
	int n = atoi(argv[1]);
	
	// creating joinable thread with func thread_func
	if(pthread_create(&thread, NULL, &thread_func, NULL) != 0) {
		fprintf(stderr, "Error\n"); 
		exit(0);
	}
	
	// sleep for arg[1] seconds
	sleep(n);

	// push function cleanHandler on the top of some stack
	// this function will automatically executed
	// when thread closed with pthread_cancel or pthread_exit
	pthread_cleanup_push(cleanHandler, NULL);
	
	// cancelling thread
	pthread_cancel(thread);
	
	// removing function from the top of the stack
	// and execute this function if flag != 0
	pthread_cleanup_pop(1);
	
	
	// compare thread IDs
	// if self thread not equal to thread
	// we join thread
	// ohhh
	// OK
	// whatever
	// recieving 
	if (!pthread_equal(pthread_self(), thread))
		pthread_join(thread, &res);

	// print some text to stderr, if thread was cancelled
	if (res == PTHREAD_CANCELED)
		fprintf(stderr, "Main thread finished thread's work\n");

	printf("End\n");
	return 0;
}
