#include <iostream>
#include <windows.h>  
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

void * child_func_iteration(void * args){
	int iter = *(int*)args;
	for(int i = 0; i < iter; i++){
		cout<<"Child Thread. Iteration: \n"<< i;
	}
	return NULL;
}

void * child_func_pseudo(void * args){
	srand(time(NULL));
	int num;
	int waitedFor = 5;
	int iter = *(int*)args;
	for(int i = 0; i < iter; i++){
		num = rand()%iter;
		if(num == waitedFor){
			cout<<"Waited value was found\n"<< waitedFor;
			return NULL;
		}
		cout<<"Child Thread. Pseudo: "<< num;
	}
	return NULL;
}

int main (){
	int iterations = 10;
	int res0, res1, pdata;
	pthread_t thread0, thread1;
	res0 = pthread_create(&thread0, NULL, &child_func_iteration, &iterations);
	res1 = pthread_create(&thread1, NULL, &child_func_pseudo, &iterations);
	if(res0 != 0 || res1 != 0){
		cout<<stderr<< "ERROR\n";
	}
	pthread_join(thread0, (void *)&pdata);
	pthread_join(thread1, (void *)&pdata);
	cout<<"End of the program\n";
	return 0;
}

