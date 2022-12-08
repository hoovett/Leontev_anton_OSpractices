#include <iostream>
#include <cmath>
using namespace std;

long func1(long x){
	x = exp(abs(-x))*sin(x);
	return x;
}

long func2(long x){
	x = exp(abs(-x))*sin(x);
	return x;
}

int main(){
	long x;
	cout << "Enter the value \n";
	cin >> x;
	cout << func1(x)<<"\n";
	cout << func2(x);
	return 0;
}


