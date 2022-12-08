#include <time.h>
#include <stdlib.h>  
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(){
	
	srand(time(NULL));
	int point_numb=0, mean=0, sum=0, module_sum=0, Neg_numb=0,more_than_mean=0;
	cout<<more_than_mean;
	cout<<"Enter quantity of points: ";
	cin>>point_numb;
	cout<<"\n";
	int arr[point_numb];
	for(int x=0;x<point_numb;x++){
		arr[x]=rand()% 201-200;
	}
	
	for(int x=0;x<point_numb;x++){
		sum+=arr[x];
	}
	mean=sum/point_numb;
	
	for(int x;x<point_numb;x++){
		if(arr[x]<0){
			Neg_numb=x+1;
			break;
		}
	}
	
	for(;Neg_numb<point_numb;Neg_numb++){
		module_sum+=abs(arr[Neg_numb]);
	}
	
	for(int x;x<point_numb;x++){
		if(arr[x]>mean){
			
			more_than_mean++;
			cout<<more_than_mean;
		}
	}
	
	cout<<"Quantity of the elements that is bigger than mean: "<<more_than_mean<<"\n";
	cout<<"Sum of absolute of elements that are located after the first negative element: "<<module_sum;
}
