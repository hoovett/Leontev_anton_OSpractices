#include <time.h>
#include <stdlib.h>  
#include <iostream>
#include <string>

using namespace std;

int GetRandomNumber(int min, int max)
{  
  srand(time(0));

  int num = min + rand() % (max - min + 1);

  return num;
}

int game(int total_score){

	int slot1, slot2, slot3;
	while (total_score>100){
		cout<<"Curent score: " << total_score << "\n";
		cout<<"Pull the arm\n";
		cin;
		
		total_score-=100;
		slot1= GetRandomNumber(1,7);
		slot2= GetRandomNumber(1,7);
		slot3= GetRandomNumber(1,7);
		cout<<slot1<<" "<<slot2<<" "<<slot3<<"\n";
		
		switch(slot1){
			
			case 0:{
				
				switch(slot2){
					case 0:{
						
						switch(slot3){
							case 0:{
								total_score+=100;
								cout<<"Congrats!!!\n+100\n";
							break;
							}
							default: cout<< "try again\n";
							
						}
						
					break;
					}
					default: cout<< "try again\n";
				}
				break;
			}
			
			case 1:{
				
				switch(slot2){
					case 1:{
						
						switch(slot3){
							case 1:{
								total_score+=150;
								cout<<"Congrats!!!\n+150\n";
							break;
							}
							default: cout<< "try again\n";
						}
						
					break;
					}
					default: cout<< "try again\n";
				}
				
				break;
			}
			
			case 2:{
				
				switch(slot2){
					case 2:{
						
						switch(slot3){
							case 2:{
								total_score+=200;
								cout<<"Congrats!!!\n+150\n";
							break;
							}
							default: cout<< "try again\n";
						}
						
					break;
					}
					default: cout<< "try again\n";
				}
				
				break;
			}
			
			case 3:{
				
				switch(slot2){
					case 3:{
						
						switch(slot3){
							case 3:{
								total_score+=250;
								cout<<"Congrats!!!\n+250\n";
							break;
							}
							default: cout<< "try again\n";
						}
						
					break;
					}
					default: cout<< "try again\n";
				}
				
				break;
			}
			
			case 4:{
				
				switch(slot2){
					case 4:{
						
						switch(slot3){
							case 4:{
								total_score+=300;
								cout<<"Congrats!!!\n+300\n";
							break;
							}
							default: cout<< "try again\n";
						}
						
					break;
					}
					default: cout<< "try again\n";
				}
				
				break;
			}
			
			case 6:{
				
				switch(slot2){
					case 6:{
						
						switch(slot3){
							case 6:{
								return 0;
							break;
							}
							default: cout<< "try again\n";
						}
						
					break;
					}
					default: cout<< "try again\n";
				}
				
				break;
			}
			
			case 5:{
				
				switch(slot2){
					case 5:{
						
						switch(slot3){
							case 5:{
								total_score+=400;
								cout<<"Congrats!!!\n+400\n";
							break;
							}
							default: {
								total_score+=200;
								cout<<"Congrats!!!\n+200\n";
							}
						}
						
					break;
					}
					default: {
					total_score+=100;
					cout<<"Congrats!!!\n+100\n";
					}
				}
				
				break;
			}
			
			case 7:{
				
				switch(slot2){
					case 7:{
						
						switch(slot3){
							case 7:{
								return 1;
							break;
							}
							default: {
								total_score+=300;
								cout<<"Congrats!!!\n+300\n";
							}
						}
						
					break;
					}
					default: {
					total_score+=150;
					cout<<"Congrats!!!\n+150\n";
					}
				}
				
				break;
			}
			
			default: cout<< "try again\n";
		}
		
	}
	cout<<"better luck next time...";
	return 0;
}

int main(){

  int number;
  
  int total_score = 5000;
  cout << "Your score is :" << total_score << "\n";
cout<<"Enter something to start...";
cin;


number= game(total_score);
if (number==1) cout<<"!!!!JACKPOT!!!!";
if (number==0) cout<<"better luck next time...";
return 0;
  
}


