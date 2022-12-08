#include <iostream>
#include <windows.h>  
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

long double factorial(int n){
    if (n == 0 || n==1)
        return 1;
    else
    {
        return n * factorial(n - 1);
    }
}

int simple(int n){
	for(int i = 2; i <= n/2; i++) 
		if((n%i)==0) 
			return 0;
return 1;
}

void * child_func_katalana(void * args){
	int n = 1;
	int iter = *(int*)args;
	int *pdataKatalana = malloc(sizeof(int)*iter*10);;
	for(int i = 0; i < iter; i++){
		pdataKatalana[i] = factorial(2*i)/(factorial(i+1)*factorial(i));
	}
	return (void *)pdataKatalana;
}

void * child_func_simple(void * args){
	int iter = *(int*)args;
	int *pdataSimple = malloc(sizeof(int)*iter*10);
	for(int i = 2, j = 0; j < iter; i++){
		if(simple(i) == 1){
			pdataSimple[j] = i;
			j++;
		}	
	}
	return (void *)pdataSimple;
}

int main (){
	int iterations = 10;
	int res0, res1;
	int *pdataKatalana;
	int *pdataSimple; 
	pthread_t thread0, thread1;
	
	res0 = pthread_create(&thread0, NULL, &child_func_katalana, &iterations);
	res1 = pthread_create(&thread1, NULL, &child_func_simple, &iterations);
	if(res0 != 0 || res1 != 0){
		cout<<stderr<<"ERROR\n";
	}
	
	pthread_join(thread0, (void *)&pdataKatalana);
	pthread_join(thread1, (void *)&pdataSimple);
	
	cout<<"CHECK KATALANA\n";
	for(int i = 0; i < iterations; i++)
		cout<< pdataKatalana[i]<<endl; 
	cout<<"CHECK SIMPLE\n";
	for(int i = 0; i < iterations; i++)
		cout<< pdataSimple[i];
		
	free(pdataKatalana);
	free(pdataSimple);
	return 0;
}
