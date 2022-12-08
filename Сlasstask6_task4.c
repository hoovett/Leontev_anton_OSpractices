#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_func(void *arg){	
	int n = 100000;
	int m = 1;
	int i;
	int x = 1;
	double p = 0;

	// enable cancellation
	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) != 0) 
		fprintf(stderr, "Setcanselstate error!\n");	
		
	// setting defaul type of cancellation
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	
	// calculating pi
	for(i = 0; i < n; i++){
		p += x * (1/(double)m);
		m += 2;
		x = -x;
		printf("Pi = %.5f\n", p*4);
		
		// init cancellation point here
		pthread_testcancel();			
	}
	printf("Final Pi = %.2f\n", p*4);
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
	// sleep for arg[1] seconds
	sleep(n);
	
	// cancelling thread
	pthread_cancel(thread);
	
	// recieving exit status of the thread to status	
	if ((pthread_join(thread, (void*)&status) != 0)) {
		printf("Join error\n"); 
		exit(0);
	}	
	
	// checking recieved status
	if (status == PTHREAD_CANCELED) 
		printf("Thread canceled\n");
	else
		printf("Thread finished by itself\n");		
	
	pthread_attr_destroy(&attr);
	printf("End\n");
	return 0;
}
