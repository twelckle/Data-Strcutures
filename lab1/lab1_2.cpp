#include<iostream>
using namespace std;

int main()
{
	float previous, current; 
	cout<<"Enter the current meter reading: ";
	cin>>current;
	cout<<"Enter previous meter reading: ";
	cin>>previous;
	float consumed = current - previous;
	float cost = 0;

	if(consumed<=100) cost = consumed * 10;
	else if(consumed<=200) cost = (consumed-100)*20 + 1000;
	else if(consumed<=500) cost = (consumed-200)*50 + 3000;
	else cost = (consumed-500)*100 + 18000;

	cout<<"The cost of electricity bill is: "<< cost/100.0 << " AED"<<endl;






	return 0;
}