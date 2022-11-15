#include<iostream>
using namespace std;

int main(){

	int number;
	cout<<"Please enter a number: ";
	cin>>number;
	string prime = " is";
	if(number == 1 || number == 0) prime = " is not"; //0 and 1 are excpetions to my loop
	else{

		for(int i=2; i<(number/2)+1;i++){ //checks to see if number n has a factor. If so number is not prime.
			if(number%i==0){
				prime = " is not";
				break;
			}
		}
	}
	cout<<number<<prime<<" a prime number."<<endl;


	return 0;
}