#include <iostream>
#include <windows.h>  
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;


struct thread_arg{
	char * name;
	char * str;
	int j;
};

void * child_func(void * arg){
	struct thread_arg targ = *(struct thread_arg *) arg;
	for(int i = 0; i < targ.j; i++){
		cout<< "Thread "<< targ.name<<" "<< targ.str<<" "<< targ.j;
	}
	return NULL;
}

int main (){
	pthread_t thread0, thread1, thread2, thread3;
	struct thread_arg targ[4] = {};
	const char *names[4] = {"Name1", "Name2", "Name3", "Name4"};
	const char *strs[4] = {"Str1", "Str2", "Str3", "Str4"};
	for(int i = 0; i < 4; i++){
		targ[i].name = (char*)names[i];
		targ[i].str = (char*)strs[i];
		targ[i].j = i+1;
	}
	int res;
	res = pthread_create(&thread0, NULL, &child_func, &targ[0]);
	res = pthread_create(&thread1, NULL, &child_func, &targ[1]);
	res = pthread_create(&thread2, NULL, &child_func, &targ[2]);
	res = pthread_create(&thread3, NULL, &child_func, &targ[3]);
	
	if(res != 0){
		cout<<stderr<< "ERROR"<<endl;
	}
	Sleep(1);
	return 0;
}




