#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// VERY USEFUL
// MUCH KEY
// MANY BENEFIT
static pthread_key_t thread_key;

void *thread_func(void *arg){	
	int id = *(int*) arg, i, stringsAmount, r;

	
	char* str = "Random number is";
	// setting key value of the thread to str
	pthread_setspecific(thread_key, (void*) str);
	
	// recieving the value of the key
	char* spec = (char*) pthread_getspecific(thread_key);	
	
	// lets print here some random number of strings
	// each string consist of some useless text and random number
	stringsAmount = 1 + rand() % 10;	
	for (i = 0; i < stringsAmount; i++){
		r = 1 + rand() % 10;
		printf("I'm thread #%d. %s %d\n", id, spec, r);
	}	
	// lets go to sleep, to the end of life
	sleep(stringsAmount);	
}
	
int main(int argc, char* argv[]){	
	if (argc != 2) {
		printf("Wrong number of arguments\n"); 
		exit(0);
	}	
	srand(time(NULL));

	// here we have an array of threads
	int n = atoi(argv[1]);	
	pthread_t threads[n];	
	int i;

	// key is visible to all threads in the process
	// but value of the key is uniq for every thread
	pthread_key_create(&thread_key, NULL);
		
	// creating n joinable threads with func thread_func every second
	for(i = 0; i < n; i++){
		if(pthread_create(&(threads[i]), NULL, &thread_func, &i) != 0){
			printf("Error\n");
			exit(0);
		}
		sleep(1);
	}	
	
	// waiting until all threads will be finished
	for (i = 0; i < n; i++){
		if ((pthread_join(threads[i], NULL) != 0)) {
			fprintf(stderr, "Join error\n"); 
			exit(0);
		}
	}	
	printf("End\n");
	return 0;
}
