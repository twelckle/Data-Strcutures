#include<iostream>
using namespace std;

int main()
{
	float highest;
	int frequency;

	for(int i = 0; i<10; i++){
		float test;
		cout<<"Enter "<<i+1<<"th number: ";
		cin>>test;

		if (i == 0){
			highest = test;
			frequency = 1; }
		else{
			if(test == highest) frequency++;
			else if(test<highest) continue;
			else{
				highest = test;
				frequency = 1;
			}
		}
	}

	cout<<"Max = "<<highest<<endl<<"Occurrence = "<<frequency<<endl;


	return 0;
}