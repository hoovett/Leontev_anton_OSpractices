#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int* checkArr;


// this function prints array
void *det_thread_func(void *arg){
	// array can be still empty 
	sleep(0.5);
	
	// somehow we get i here	
	int n = *(int*)arg, i, flag;
	
	// every second doing something
	while(1){
		flag = 0;
		
		// at least one element in array = 0 -> flag = 1
		for(i = 0; i < n; i++){		
			if (checkArr[i] == 0) 
				flag = 1;			
		}	
			
		// don't have zeros in array -> exit
		// have zeros == we still have to fill array to the end
		if (flag = 0) 
			break;
			
		// print array		
		for (i = 0; i < n; i++){
			printf(":%d", checkArr[i]);
		}
		printf("\n");
		sleep(1);		
	}
}

void *join_thread_func(void *arg){	
	// num = i, somehow this works
	int num = *(int *)arg, i, r;

	sleep(num);
	
	// put generated random number 1..10
	// to array in position num
	r = 1 + rand() % 10;
	printf("Random number %d\n", r);
	checkArr[num] = r;
	// thread going to sleep on randomed number of sec
	sleep(r);	
	return NULL;
}
	
int main(int argc, char* argv[]){	
	if (argc != 2) {
		printf("Wrong number of arguments\n");
		exit(0);
	}
		
	srand(time(NULL));
	
	pthread_attr_t attr;
	pthread_t detached_thread, joinable_thread;		
	int n = atoi(argv[1]);
	int i;
	checkArr = (int*)calloc(n, sizeof(int));


	// init attr
	pthread_attr_init(&attr);
	// set attr to create detached thread
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(pthread_create(&detached_thread, &attr, &det_thread_func, &n) != 0){
		fprintf(stderr, "Error\n");
		exit(0);
	}
	


	// creating n joinable threads
	// every second creating new thread with argument 0..n-1
	// 
	for(i = 0; i < n; i++){
		if(pthread_create(&joinable_thread, NULL, &join_thread_func, &i) != 0){
			printf("Error\n");
			exit(0);
		}
		sleep(1);
	}	


	
	// joining to the last joinable thread
	if ((pthread_join(joinable_thread, NULL) != 0)) {
		printf("Join error\n"); 
		exit(0);
	}	
	
	// and finish
	pthread_attr_destroy(&attr);
	printf("End\n");
	return 0;
}
