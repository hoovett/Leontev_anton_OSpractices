#include <time.h>
#include <stdlib.h>  
#include <iostream>
#include <string>

using namespace std;



int main(){
	
	srand(time(NULL));
	int number_OfPoints;
	int Lowest_numb;
	cout<< "Enter the quantity of points: ";
	cin>> number_OfPoints;
	int arr[number_OfPoints];
	
	for(int x=0;x<number_OfPoints;x++){
		arr[x]=rand();
		
	}
	
	for(int x=0;x<number_OfPoints;x++){
	cout<<arr[x]<<" ";
		
	}
	cout<<"\n";
	for(int loop=0;loop<number_OfPoints;loop++){
	
	for(int x=0;x<number_OfPoints;x++){
		if(arr[x]<arr[x+1]) Lowest_numb=x;
		
	}
	arr[Lowest_numb+1]+=arr[Lowest_numb];
	arr[Lowest_numb]=0;
	
	for(int temp;Lowest_numb<number_OfPoints;Lowest_numb++){
	
	temp=arr[Lowest_numb+1];
	arr[Lowest_numb+1]=arr[Lowest_numb];
	arr[Lowest_numb]=temp;
	
	}
	}
	
	for(int x=0;x<number_OfPoints;x++){
		cout<<arr[x]<<" ";
		
	}
	
	
	cout<<"\n"<<arr[0];
	
}
