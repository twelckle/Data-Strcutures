//============================================================================
// Name         : lab2_1
// Author       : Theo Welckle
// Version      : 1
// Date Created : Feb 1
// Date Modified: Feb 1
// Description  : Find Min. and Max. values from an Array passed to a function 
//                using pass-by reference. 
//============================================================================
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void findMinMax(int[],int, int&, int&);	//function declaration

int main(void)
{
	//Declare variables
	int arraySize;
	int minValue;
	int maxValue;


	//Prompt user for the array size
	cout<<"Enter Size of the Array: ";
	cin>>arraySize;

	//Create dynamic array
	int *carray = new int[arraySize];

	//Pass System time to to srand function to create different random numbers everytime the program starts
	srand(time(NULL));

	//Populate the array with random values 0-100
	for(int i=0; i<arraySize; i++){
		carray[i] = rand() % 100;
	}

	//Call function finMinMax()
	findMinMax(carray, arraySize, minValue, maxValue);

	//Print the values of array followed by min and max values
	for(int i = 0; i<arraySize; i++)
		cout<<"array["<<i<<"] = "<<carray[i]<<endl;
	cout<<"Min: "<<minValue<<endl;
	cout<<"Max: "<<maxValue<<endl;

	//Do Necessary cleanup, e.g. delete dynamically allocated memory.
	delete [] carray;
	return EXIT_SUCCESS;
}

//Function Definition
void findMinMax(int array[], int arraySize, int& min, int& max)
{
	for(int i = 0; i<arraySize; i++){

		//initialize values for min and max
		if (i == 0) {min = array[i]; max = array[i];}

		//change values of min and max accordingly. 
		else if(array[i]>max) {max = array[i];}
		else if(array[i]<min) {min = array[i];}

	}
}
