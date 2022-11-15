//============================================================================
// Name         : lab10.cpp
// Author       : 
// Version      : 1.0
// Date Created : 15-04-2022
// Date Modified: 15-04-2022
// Description  : Binary Heap Implementation in C++
// Copyright © 2020 Khalid Mengal. All rights reserved.
//============================================================================
#include<iostream>
#include<exception>
#include<math.h>
#include<iomanip>
#include<unistd.h>
#include<sstream>
using namespace std;
class Heap
{
	private:
		int *array;
		int capacity;
		int size;
	
	public:
		Heap(int capacity);
		~Heap();
		void insert(int key);
		int removeMin();
		int getMin();
		int parent(int k);
		int left(int k);
		int right(int k);
		void siftup(int k);
		void siftdown(int k);
		void print(int k=-1);
		void sort();
	private:
		void adjustSize();
};

void listCommands()
{
	cout<<"-----------------------------------------------------------------"<<endl;
	cout<<"display            :Display the Heap"<<endl
		<<"insert <key>       :Insert a new element in the Heap"<<endl
		<<"getMin             :Get the element with Min. Key in the Heap"<<endl
		<<"removeMin          :Remove the element with Min. Key from Heap"<<endl
		<<"sort               :Sort the Heap"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;
}
//=============================================
void demo(Heap &myHeap)
{
	srand(time(NULL));
	
	for (int i=0; i<10; i++)
	{
		int n = rand()%100;
		cout<<"Inserting "<<n<<endl;
		myHeap.insert(n);
		system("clear");
		myHeap.print();

	}
}
//=============================================
int main()
{

	Heap myHeap(15);
	string user_input;
	string command;
	string argument;

	listCommands();

	while(true)
	{
		try
		{
			cout<<">";
			getline(cin,user_input);

			// parse userinput into command and parameter(s)
			stringstream sstr(user_input);
			getline(sstr,command,' ');
			getline(sstr,argument);
			
		
		         if(command =="display" or command=="d")        myHeap.print();
			else if(command =="insert"  or command=="i")        {myHeap.insert(stoi(argument)); myHeap.print();}
			else if(command =="getMin")        					cout<<"Min Key = "<<myHeap.getMin()<<endl;
			else if(command =="removeMin"  or command=="r")     {cout<<myHeap.removeMin()<<" has been removed..!"<<endl; myHeap.print();}     
			else if(command =="sort")          					myHeap.sort();
			else if(command == "help")         					listCommands();
			else if(command == "demo")         					demo(myHeap);
			else if(command == "exit" or command == "quit") 	break;
			else cout<<"Invalid command !!!"<<endl;
	
		}
		catch (exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}
	}
	return EXIT_SUCCESS;
}
//==================================================
// Constructor
Heap::Heap(int capacity)
{
	array = new int[capacity];
	this->capacity = capacity;
	size = 0;
}
//Destructor
Heap::~Heap()
{
	delete[] array;
}
// Insert an element in Heap keeping the Heap property intact 
void Heap::insert(int key)
{
	//if size needs to be increased call function. Otherwise add element to the end of the array and use
	//siftup to ensure the element ends in the right place. update size
	if(size == capacity) adjustSize();
	array[size] = key;
	siftup(size);
	size++;
}
// Remove the minimum value from Heap keeping the Heap property intact
int Heap::removeMin()
{

	if(size == 1) return array[0];

	//swap the minimum and the last element in the array. Therfore first and last. 
	int smallestNumber = array[0];
	array[0] = array[size-1];
	array[size-1] = smallestNumber;
	size--;


	//call shift down to ensure the heap properties still stand.
	siftdown(0);

	return smallestNumber;
}
// Return (but don't remove) the minimum value from the Heap
int Heap::getMin()
{
	//returns first element
	return array[0];
}
// Returns the index of the parent of the node i
int Heap::parent(int k)
{
	return int((k-1)/2);
}
// Returns the index of the left child of the node i
int Heap::left(int k)
{
	return (2*k + 1);
}
// Returns the index of the right child of the node i
int Heap::right(int k)
{
	return (2*k + 2);
}

// Sift-up an element at index k
void Heap::siftup(int k)
{
	//if parent key is larger then child flip and recurisivly call siftup for the parent index.
	int parentIndex = parent(k);
	if(array[parentIndex]>array[k]){
		int temp = array[parentIndex];
		array[parentIndex] = array[k];
		array[k] = temp;
		siftup(parentIndex);
	}

}

// Sift-down an element at index k
// 1. if element has no children do nothing
// 2. if element has only a left child which is smaller than element then swap the element with its left child
// 3. if element has both children and smaller child is also smaller than the node then swap it with that node
// 4. keep repeating step 1-3 until the element/node reaches to its correct position
void Heap::siftdown(int k)
{
	int leftI = left(k);
	int rightI = right(k);

	//if element only has a left child, and the left child is smaller then the node, swap and recursively call the function.
	if(2*k+2 == size && array[leftI] < array[k]){
		int temp = array[leftI];
		array[leftI] = array[k];
		array[k] = temp;
		siftdown(leftI);
	}

	//if the element has 2 children. Determine the minimum of those two children. Then see if that number is 
	//smaller than the node number. If so swap the two elements and continue to call siftdown. 
	else if(2*k+2 < size){
		int number = min(array[leftI], array[rightI]);
		if(array[k]>number){
			if(number == array[leftI]){
				int temp = array[leftI];
				array[leftI] = array[k];
				array[k] = temp;
				siftdown(leftI);
			}
			else{
				int temp = array[rightI];
				array[rightI] = array[k];
				array[k] = temp;
				siftdown(rightI);
				
			}
		}
	}

}


//==================================================================
// This method prints a Heap in 2D format. 
//Optional argument k is the index of element which will be printed in red color
//if not argument provided, the entire array/tree will be printed in white color.
void Heap::print(int k)
{
	//cout << "\033[1;31mbold red text\033[0m\n";
	if(size >0)
	{
		int levels = int(log2(size));

		int spaces[levels+1];
		spaces[levels]=0;

		for(int j=levels-1; j>=0; j--)
		{
				spaces[j]=2*spaces[j+1]+1;
		}
		
		int level=0;
		for (int i=0; i<size; i++)
		{
			if(i == (pow(2,level)-1))
			{
				cout<<endl<<endl;
			
				for(int k=0; k<spaces[level]; k++)
				cout<<"   ";
				level++;
		
			}
			if(i==k)
				cout<<std::left<<"\033[1;31m"<<setw(3)<<array[i]<<"\033[0m";
			else
				cout<<std::left<<setw(3)<<array[i];
			
			if(level>1)
			{
				for(int k=0; k<spaces[level-2]; k++)
					cout<<"   ";
			}
			
		}

		cout<<endl;
		for(int i=0; i<spaces[0]*log2(size/2)+4; i++)
		cout<<"__";
		cout<<endl;
	}

}
//=====================================
// This method will sort the internal array of heap using an Auxilary heap
// Hint: Add element of the array in the Auxilary heap first and they keep 
//       extractin the min. value and write it on the original array

void Heap::sort()
{
	//todo
	//create new array. Remove minimum from old array, and add to new array until no elements remain in the old array.
	int* newArray = new int[size];
	int originalsize = size;
	for(int i = 0; i<originalsize; i++){
		newArray[i] = removeMin();
	}

	//delete old array. set array to new array. reupdate size. 
	delete[] array;
	array = newArray;
	size = originalsize;
	print();

}
//=============================================
void Heap::adjustSize()
{
	int *newArray = new int[capacity*2];
	for(int i=0; i<capacity; i++)
		newArray[i] = array[i];
	delete[] array;
	array = newArray;
	capacity = capacity*2;	
}
//=============================================