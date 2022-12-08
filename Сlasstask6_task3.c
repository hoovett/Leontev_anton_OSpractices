#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *thread_func(void *arg){	
	int n = *(int*)arg, i;	

	// disabling ability to be cancelled
	if (pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL) != 0) 
		printf("Setcanselstate error!\n");

	// print iteration every second
	for(i = 0; i < n*2; i++){
		printf("Iteration %d\n", i);
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
	
	// creating joinable thread with func thread_func
	pthread_attr_init(&attr);
	if(pthread_create(&thread, &attr, &thread_func, &n) != 0) {
		printf("Error\n"); 
		exit(0);
	}
	// sleeping for arg[1] seconds
	sleep(n);
	
	// trying to cancel thread
	if (pthread_cancel(thread) != 0) 
		printf("Cancel error!\n");
	
	// joining thread, and recieving exit status to status
	if ((pthread_join(thread, (void*)&status) != 0)) {
		printf("Join error\n"); 
		exit(0);
	}	
	
	// checking status
	if (status == PTHREAD_CANCELED) 
		printf("Thread canceled\n");
	else 
		printf("Thread finished by itself\n");
			
	pthread_attr_destroy(&attr);
	printf("End\n");
	return 0;
}
