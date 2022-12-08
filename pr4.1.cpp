#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        // Выводим список аргументов в цикле
        cout << "Argument " << i << " : " << argv[i] << endl;
        
    }
    int a=atoi(argv[1]), b=atoi(argv[2]), c=atoi(argv[3]), x=atoi(argv[4]);
    
    cout<<a <<" "<<b<<" "<<c<<" "<<x<<endl;
    cout<<"Value of a*x^2+b*x+c: "<<a*sqrt(x)+b*x+c;
    
    return 0; 
	
}


