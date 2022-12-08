#include <iostream>
#include<windows.h>  
#include <stdlib.h>


#include <pthread.h>
using namespace std;



void * child_func(void * args){
	for(int i = 0; i < 5; i++){
		cout <<"Child Thread. Iteration: "<< i;
		Sleep(1);
	}
	return NULL;
}

int main (){
	pthread_t thread;
	int res;
	res = pthread_create(&thread, NULL, &child_func, NULL);
	if(res != 0){
		cout<<stderr<< "ERROR\n";
	}
	for(int i = 0; i < 5; i++){
		cout<<"Main Thread. Iteration: "<<i;
		Sleep(1);
	}
	return 0;
}
