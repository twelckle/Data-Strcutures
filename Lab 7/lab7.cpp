//============================================================================
// Name         : MyVector.cpp
// Author       : Theo Welckle
// Version      : 1.0
// Date Created : 24-03-2022
// Date Modified: 24-3-2022
// Copyright    : All rights are reserved
// Description  : Vector implmentation in C++
//============================================================================
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>

using namespace std;

//out of range exception
class Out_of_range: public exception
{
	public:
		virtual const char* what() const throw()
		{
			return "Index is out of range"; 
		}
};

//range error eception
class Range_error: public exception
{
	public:
		virtual const char* what() const throw()
		{
			return "Trying to store a value which is out of range"; 
		}
};

//empty vecotr exception.
class EmptyVector: public exception
{
	public:
		virtual const char* what() const throw()
		{
			return "Vector is Empty"; 
		}
};

template <typename T>
class MyVector
{
	private:
		T *data;						//pointer to int(array) to store elements
		int v_size;						//current size of vector (number of elements in vector)
		int v_capacity;					//capacity of vector
	public:
		MyVector();						//No argument constructor
		MyVector(int cap);				//One Argument Constructor
		~MyVector();					//Destructor
		void push_back(T element);		//Add an element at the end of vector
		void insert(int index, T element); //Add an element at the index 
		void erase(int index);			//Removes an element from the index
		T& at(int index); 				//return reference of the element at index
		const T& front();				//Returns reference of the first element in the vector
		const T& back();				//Returns reference of the Last element in the vector
		int size() const;				//Return current size of vector
		int capacity() const;			//Return capacity of vector
		bool empty() const; 			//Rturn true if the vector is empty, False otherwise
		void shrink_to_fit();			//Reduce vector capacity to fit its size
		void display();
};

void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display                  : Display the Vector"<<endl
		<<"push_back <element>      : Add an element to the end of the vector"<<endl
		<<"insert <index element>   : Insert an element at location index"<<endl
		<<"erase <index>           : Remove the element from index"<<endl
		<<"at <index>               : Returns a reference to an element at a specified location"<<endl
		<<"front                    : Return the (reference of) front element"<<endl
		<<"back                     : Returns a reference to the last element of the vector"<<endl
		<<"size                     : Returns the number of elements in the vector"<<endl
		<<"capacity                 : Returns the capacity of vector"<<endl
		<<"empty                    : Tests if the vector container is empty"<<endl
		<<"shrink                   : Reduce vector capacity to fit its size (shrink_to_fit)"<<endl
		<<"exit/quit                : Exit the Program"<<endl;
}
//=======================================
int main()
{

	
	MyVector<int> myVector;
	listCommands();
	string user_input;
	string command;
	string parameter1;
	string parameter2;

	do
	{
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter1,' ');
		getline(sstr,parameter2);

		try
		{
			if(command=="display" or command=="d") 								myVector.display();
			else if(command=="push_back" or command=="p" )		myVector.push_back(stoi(parameter1)),myVector.display();
			else if(command=="insert" or command=="i")		    myVector.insert(stoi(parameter1),stoi(parameter2)),myVector.display();
			else if(command=="erase" or command=="e")		    myVector.erase(stoi(parameter1)),myVector.display();
			else if(command=="at" or command=="a")			    cout<<myVector.at(stoi(parameter1))<<endl;
			else if(command=="front" or command=="f")			cout<<myVector.front()<<endl;
			else if(command=="back" or command=="b")			cout<<myVector.back()<<endl;
			else if(command=="size" or command=="s")            cout<<myVector.size()<<endl;
			else if(command=="capacity" or command=="c")        cout<<myVector.capacity()<<endl;
			else if(command=="empty" or command=="e")			cout<<boolalpha<<myVector.empty()<<endl;
			else if(command=="shrink")          				myVector.shrink_to_fit(),myVector.display();
			else if(command == "help" or command=="?")			listCommands();
			else if(command == "exit" or command=="quit")			break;
			else 								cout<<"Invalid Commad !!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}while(command!="exit" and command!="quit");

	return EXIT_SUCCESS;
}
#ifndef _WIN32
//======================================
template <typename T>
void MyVector<T>::display()
{
	cout<<"╔════";
	for(int i=0; i<v_capacity-1; i++)
		cout<<"╦════";	
	cout<<"╗ size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		if(i<v_size)
			cout<<"║"<<setw(4)<<data[i];
		else
			cout<<"║"<<setw(4)<<" ";		
	}
	if(v_size==0) cout<<"║    ";
	cout<<"║"<<endl<<"╚════";
	for(int i=0; i<v_capacity-1; i++)
		cout<<"╩════";
	cout<<"╝ capacity = "<<v_capacity<<endl;	
}
//======================================
#else
template <typename T>
void MyVector<T>::display()
{
	cout<<"+";
	for(int i=0; i<v_capacity; i++)
		cout<<"---+";	
	cout<<" size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		if(i<v_size)
			cout<<"|"<<setw(3)<<data[i];
		else
			cout<<"|"<<"   ";		
	}
	cout<<"|"<<endl<<"+";
	for(int i=0; i<v_capacity; i++)
		cout<<"---+";
	cout<<" capacity = "<<v_capacity<<endl;	
}
#endif


//constructor with 0 arguments
template <typename T>
MyVector<T>::MyVector(){
	data = new T[0];
	v_size = 0;
	v_capacity = 0;
}

//deconstructor
template <typename T>
MyVector<T>::~MyVector(){
	delete data;
}

//constructor with capacity argument
template <typename T>
MyVector<T>::MyVector(int cap){
	data = new T[cap];
	v_size = 0;
	v_capacity = cap;
}

template <typename T>
void MyVector<T>::push_back(T elem){

	//if vector is full extend the array by multiplying by 2. amortization
	if(v_size>=v_capacity){
		T *newData;

		//case when vector is completely empty.
		if(v_capacity==0){ 
			newData = new T[1];
			v_capacity = 1;
		}

		//all other cases. Create array with 2X the space. Update capacity
		else{
			newData = new T[v_capacity*2];
			v_capacity *= 2;
		}

		//transfer all data from old array to new one. Reassign the data attribute to the new array.
		for(int i = 0; i<v_size; i++){
			newData[i] = data[i];
		}
		data = newData;
	}

	//insert element to back of the array. update the size. 
	data[v_size] = elem;
	v_size++;

}

template <typename T>
void MyVector<T>::insert(int index, T element){
	//if index is out of range, exception is thrown
	if(index>v_capacity-1){
		throw Range_error();
	}

	//if vector is full extend the array by multiplying by 2. amortization
	if(v_size>=v_capacity){
		T *newData;

		//case when vector is completely empty.
		if(v_capacity==0){ 
			newData = new T[1];
			v_capacity = 1;
		}

		//all other cases. Create array with 2X the space. Update capacity
		else{ 
			newData = new T[v_capacity*2];
			v_capacity *= 2;
		}

		//transfer all data from old array to new one. Reassign the data attribute to the new array.
		for(int i = 0; i<v_size; i++){
			newData[i] = data[i]; 
		}
		data = newData;
	}
	//if index given by user is greater then the current size and smaller then the capacity, push element to the back.
	if(index>=v_size){
		push_back(element);
	}

	//move all elements at and after user supplied index up by one. Then insert the element into the index position.
	else{
		for(int i = v_size-1; i >= index; i--){
			data[i+1] = data[i];
		}
		data[index] = element;
		v_size++;
	}
}

template <typename T>
void MyVector<T>::erase(int index){

	//if index is out of range exception is thrown
	if(index>=v_size){
		throw Out_of_range();
	}

	//moves all data up in the array by one, then adjusts the size of the vector.
	for(int i = index; i<v_size; i++){
		data[i] = data[i+1];
	}
	v_size--;
}

//returns the index of an object in the vector unless the index is out of bounds in which an exception is thrown.
template <typename T>
T& MyVector<T>::at(int index){
	if(index>= v_size){
		throw Out_of_range();
	}
	return data[index];
	
}

//returns the front element unless the vector is empty, then throws an excetion
template <typename T>
const T& MyVector<T>::front(){
	if(empty())throw EmptyVector();
	return data[0];
}

//returns the back element unless the vector is empty, then throws an excetion
template <typename T>
const T& MyVector<T>::back(){
	if(empty())throw EmptyVector();
	return data[v_size-1];
}

// returns the size of the vector.
template <typename T>
int MyVector<T>::size() const{
	return v_size;
}

//returns the capacity of the vector
template <typename T>
int MyVector<T>::capacity() const{
	return v_capacity;
}

//returns whether the vector is empty or not
template <typename T>
bool MyVector<T>::empty() const{
	return v_size == 0;
}

//shrinks the size of the vector by making the capacity equal the size. 
template <typename T>
void MyVector<T>::shrink_to_fit(){
	v_capacity = v_size;
}
