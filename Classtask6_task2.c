#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_func(){	
	int i = 0;

	// enable cancellation
	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) != 0) 
		printf("Setcanselstate error!\n");
	
	// setting cancellability state
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL) != 0)
		printf("Setcanseltype error!\n");
		
	// infinite loop
	// print current iteration
	while(1){
		printf("Iteration %d\n", i++);
		sleep(1);			
	}
}
	
int main(int argc, char* argv[]){	
	if (argc != 2) {
		printf("Wrong number of arguments\n"); 
		exit(0);
	}	
		
	pthread_attr_t attr;
	pthread_t thread;
	int *status;		
	int n = atoi(argv[1]);
	
	// init attr, and create joinable thread with func thread_func
	pthread_attr_init(&attr);
	if(pthread_create(&thread, &attr, &thread_func, NULL) != 0) {
		printf("Error\n"); 
		exit(0);
	}	
	
	// sleep for arg number of seconds
	sleep(n);
	
	// asking thread to close
	if (pthread_cancel(thread) != 0) 
		printf("Cancel error!\n");
	
	// joining thread
	// and recieving exit status to status
	if ((pthread_join(thread, (void*)&status) != 0)) {
		printf("Join error\n"); 
		exit(0);
	}	
	
	// checking exit status
	if (status == PTHREAD_CANCELED) 
		printf("Thread canceled\n");
	else 
		printf("Thread finished normaly\n");
			
	pthread_attr_destroy(&attr);
	printf("End\n");
	return 0;
}
