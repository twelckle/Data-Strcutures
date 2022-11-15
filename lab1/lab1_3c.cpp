#include<iostream>
using namespace std;

int main(){
	/*
	Write a program that asks the user to enter an integer number N,
 	then displays the number(count) of prime numbers that are smaller than N.
	*/


	int number;
	cout<<"Please enter a number: ";
	cin>>number;
	int counter = 1;
	bool prime;

	for(int k = number-1; k>2; k--){ //loops through interval (n,2)
		prime = true;
		for(int i=2; i<(k/2)+1;i++){ //checks to see if value k(above) is prime
			if(k%i==0){
				prime = false;
				break;
			}
		}
		if (prime) {
			counter++;}
	
	}

	if(number == 0 || number == 1 || number == 2) counter = 0;

	cout<<"The number of prime numbers smaller than "<<number<<" is: "<<counter<<endl;




	return 0;
}